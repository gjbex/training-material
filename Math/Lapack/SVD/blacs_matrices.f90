module blacs_matrices
    implicit none

    integer, parameter :: DLEN_ = 9, DTYPE_ = 1, CTXT_ = 2, &
                          M_ = 3, N_ = 4, MB_ = 5, NB_ = 6, &
                          RSRC_ = 7, CSRC_ = 8, LLD_ = 9
    logical :: blacs_is_verbose = .FALSE.
    
contains

    subroutine blacs_start(my_id, context)
        use mpi
        implicit none
        integer, intent(out) :: my_id, context
        integer, dimension(2) :: dims
        integer :: nr_procs, ierror, nr_proc_rows, nr_proc_cols, &
                   my_proc_row, my_proc_col
        call blacs_initialize(my_id, context, nr_procs)
        ! create the processor grid, row-major
        dims = 0
        call MPI_DIMS_CREATE(nr_procs, 2, dims, ierror)
        nr_proc_cols = dims(1)
        nr_proc_rows = dims(2)
        if (blacs_is_verbose .and. my_id == 0) then
            print 1001, nr_proc_rows, nr_proc_cols 
            1001 format(1X, 'proc grid: ', I3, ' x ', I3)
        end if
        if (nr_proc_rows*nr_proc_cols /= nr_procs) then
            if (my_id == 0) print *, 'choose number of processors better'
            call MPI_ABORT(MPI_COMM_WORLD, ierror)
        end if
        call BLACS_GRIDINIT(context, 'R', nr_proc_rows, nr_proc_cols)
        ! retrieve processor grid dimensions and coordinates for this
        ! process
        call BLACS_GRIDINFO(context, nr_proc_rows, nr_proc_cols, &
                            my_proc_row, my_proc_col)
    end subroutine blacs_setup

    subroutine blacs_initialize(my_id, context, nr_procs)
        implicit none
        integer, intent(out) :: my_id, context, nr_procs
        ! note that nr_procs must not be a parameter
        ! find out id and number of processors
        call BLACS_PINFO(my_id, nr_procs)
        ! initialize a context
        call BLACS_GET(0, 0, context)
    end subroutine blacs_initialize

    subroutine blacs_set_topology(my_id, context, &
                                  nr_proc_rows, nr_proc_cols, &
                                  orientation, my_proc_row, my_proc_col)
        implicit none
        integer, intent(out) :: my_id, context, my_proc_row, my_proc_col
        character, intent(in) :: orientation
        integer, intent(inout) :: nr_proc_rows, nr_proc_cols
        integer :: nr_procs
        ! note that nr_procs must not be a parameter
        ! find out id and number of processors
        call BLACS_PINFO(my_id, nr_procs)
        ! initialize a context
        call BLACS_GET(0, 0, context)
        call BLACS_GRIDINIT(context, orientation, &
                            nr_proc_rows, nr_proc_cols)
        call BLACS_GRIDINFO(context, nr_proc_rows, nr_proc_cols, &
                            my_proc_row, my_proc_col)
    end subroutine blacs_set_topology

    subroutine determine_topology(nr_proc_rows, nr_proc_cols)
        use mpi
        implicit none
        integer, intent(out) :: nr_proc_rows, nr_proc_cols
        integer :: nr_procs, my_id, ierr
        integer, dimension(2) :: dims
        call BLACS_PINFO(my_id, nr_procs)
        dims = 0
        call MPI_Dims_create(nr_procs, 2, dims, ierr)
        nr_rows = dims(1)
        nr_cols = dims(2)
    end subroutine determine_topology

    subroutine init_storage(rows, cols, context, matrix_desc, local_matrix)
        use mpi
        use, intrinsic :: iso_fortran_env, only : dp => REAL64, error_unit
        implicit none
        integer, dimension(DLEN_), intent(inout) :: matrix_desc
        real(kind=dp), allocatable, dimension(:, :), &
                       intent(inout) :: local_matrix
        integer, intent(in) :: rows, cols, context
        integer :: nr_proc_rows, nr_proc_cols, my_proc_row, my_proc_col, &
                   row_block, col_block, local_rows, local_cols, info, istat
        call BLACS_GRIDINFO(context, nr_proc_rows, nr_proc_cols, &
                            my_proc_row, my_proc_col)
        ! initialize matrix descriptor
        row_block = rows/nr_proc_rows
        col_block = cols/nr_proc_cols
        local_rows = compute_dim(rows, row_block, nr_proc_rows, my_proc_row)
        local_cols = compute_dim(cols, col_block, nr_proc_cols, my_proc_col)
        if (blacs_is_verbose) then
            write (error_unit, 2001) my_proc_row, my_proc_col, &
                local_rows, local_cols, row_block, col_block
            2001 format(1X, 'proc grid pos: [', I3, ',', I3, ']: ', &
                        I3, ' x ', I3, ' (', I3, ' x ', I3, ')')
        end if
        call DESCINIT(matrix_desc, rows, cols, row_block, col_block, 0, 0, &
                      context, local_rows, info)
        ! initialize local storage
        allocate(local_matrix(local_rows, local_cols), stat=istat)
        if (istat /= 0) then
            write (error_unit, 2002) my_proc_row, my_proc_col, &
                8*local_rows*local_cols
            2002 format(1X, '(', I3, ',', I3, ') can not allocate ', &
                        I12, ' bytes for local storage')
            call MPI_ABORT(MPI_COMM_WORLD, istat)
        else
            writ (error_unit, 2003) my_proc_row, my_proc_col, &
                8*local_rows*local_cols
            2003 format(1X, '(', I3, ',', I3, ') allocated ', &
                        I12, ' bytes for local storage')
        end if
    end subroutine init_storage

    integer function compute_dim(total_len, block_len, nr_procs, id)
        implicit none
        integer, intent(in) :: total_len, block_len, nr_procs, id
        integer :: local_len, first, pos, size
        local_len = 0
        first = id*block_len + 1
        do pos = first, total_len, block_len*nr_procs
            size = min(block_len, total_len - pos + 1)
            local_len = local_len + size
        end do
        compute_dim = local_len
    end function compute_dim

    subroutine read_matrix(matrix_desc, local_matrix, in_file)
        use mpi
        implicit none
        integer, dimension(DLEN_), intent(in) :: matrix_desc
        double precision, dimension(:, :), intent(inout) :: local_matrix
        character(len=1024), intent(in) :: in_file
        integer :: rows, cols, row_block, col_block, &
                   nr_proc_rows, nr_proc_cols, &
                   my_proc_row, my_proc_col, start_row, row_incr, &
                   start_col, col_incr, local_row, local_col, row_size, &
                   buffer_size, j, context, file_pointer, &
                   ierror, jerror, istat
        integer, parameter :: LONG = selected_int_kind(13)           
        integer(kind=MPI_OFFSET_KIND) :: i, pos, row, col
        integer, dimension(MPI_STATUS_SIZE) :: status
        double precision, allocatable, dimension(:) :: buffer
        character(len=MPI_MAX_ERROR_STRING) :: error_str
        integer :: error_str_len
        rows = matrix_desc(M_)
        cols = matrix_desc(N_)
        row_block = matrix_desc(MB_)
        col_block = matrix_desc(NB_)
        context = matrix_desc(CTXT_)
        call BLACS_GRIDINFO(context, nr_proc_rows, nr_proc_cols, &
                            my_proc_row, my_proc_col)
        start_row = my_proc_row*row_block
        row_incr = nr_proc_rows*row_block
        start_col = my_proc_col*col_block
        col_incr = nr_proc_cols*col_block
        local_row = 1
        allocate(buffer(cols), stat=istat)
        if (istat /= 0) then
            print 3001, my_proc_row, my_proc_col, 8*cols
            3001 format(1X, '(', I3, ',', I3, ') can not allocate ', I12, &
                        ' bytes for buffer in read_matrix')
            call MPI_ABORT(MPI_COMM_WORLD, istat)
        end if
        call MPI_BARRIER(MPI_COMM_WORLD, ierror)
        call MPI_FILE_OPEN(MPI_COMM_WORLD, trim(in_file), MPI_MODE_RDONLY, &
                           MPI_INFO_NULL, file_pointer, ierror)
        if (ierror /= 0) then
            print *, 'error opening file'
            call MPI_ABORT(MPI_COMM_WORLD, ierror)
        end if
        do row = start_row, rows, row_incr
            row_size = min(row_block, rows - row)
            do i = 1, row_size
                local_col = 1
                do col = start_col, cols, col_incr
                    buffer_size = min(col_block, cols - col)
                    pos = 8_LONG*((row + i - 1)*cols + col)
                    call set_file_pos(file_pointer, pos, ierror)
                    if (ierror /= 0) then
                        print 3002, my_proc_row, my_proc_col, pos, &
                                    file_pointer
                        3002 format(1X, 'error seek file in [', &
                                    I3, ', ', I3, ']', ' at ', &
                                    I10, ' fp ', I10)
                        call MPI_ERROR_STRING(ierror, error_str, &
                                              error_str_len, jerror)
                        print *, ierror, trim(error_str)
                        call MPI_ABORT(MPI_COMM_WORLD, ierror)
                    end if
                    call MPI_FILE_READ(file_pointer, buffer, buffer_size, &
                                       MPI_DOUBLE_PRECISION, status, ierror)
                    if (ierror /= 0) then
                        print 3003, my_proc_row, my_proc_col, pos, &
                                    buffer_size
                        3003 format(1X, 'error reading in [', &
                                    I3 ' x ', I3, '] at ' &
                                    I10, ' size ', I10)
                        call MPI_ERROR_STRING(ierror, error_str, &
                                              error_str_len, jerror)
                        print *, ierror, trim(error_str)
                        call MPI_ABORT(MPI_COMM_WORLD, ierror)
                    end if
                    do j = 1, buffer_size
                        local_matrix(local_row, local_col + j - 1) = buffer(j)
                    end do
                    local_col = local_col + buffer_size
                end do
                local_row = local_row + 1
            end do
        end do
        call MPI_FILE_CLOSE(file_pointer, ierror)
        deallocate(buffer)
    end subroutine read_matrix

    subroutine set_file_pos(file_pointer, offset, ierror)
        use mpi
        implicit none
        integer, intent(inout) :: file_pointer
        integer, intent(in) :: offset
        integer, intent(out) :: ierror
        integer :: pos, delta, jumps, jump
        delta = 2000000000
        jumps = offset/delta
        pos = 0
        call MPI_FILE_SEEK(file_pointer, pos, MPI_SEEK_SET, ierror)
        if (ierror /= 0) return
        do jump = 1, jumps
            call MPI_FILE_SEEK(file_pointer, delta, MPI_SEEK_CUR, ierror)
            if (ierror /= 0) return
        end do
        pos = offset - delta*jumps
        call MPI_FILE_SEEK(file_pointer, pos, MPI_SEEK_CUR, ierror)
    end subroutine set_file_pos

    subroutine write_matrix(matrix_desc, local_matrix, out_file)
        use mpi
        implicit none
        integer, dimension(DLEN_), intent(in) :: matrix_desc
        double precision, dimension(:, :), intent(in) :: local_matrix
        character(len=1024), intent(in) :: out_file
        integer :: rows, cols, row_block, col_block, &
                   nr_proc_rows, nr_proc_cols, &
                   my_proc_row, my_proc_col, start_row, row_incr, &
                   start_col, col_incr, local_row, local_col, row_size, &
                   buffer_size, j, context, file_pointer, &
                   ierror, jerror, istat
        integer, parameter :: LONG = selected_int_kind(13)           
        integer(kind=MPI_OFFSET_KIND) :: i, pos, row, col
        integer, dimension(MPI_STATUS_SIZE) :: status
        double precision, allocatable, dimension(:) :: buffer
        character(len=MPI_MAX_ERROR_STRING) :: error_str
        integer :: error_str_len
        rows = matrix_desc(M_)
        cols = matrix_desc(N_)
        row_block = matrix_desc(MB_)
        col_block = matrix_desc(NB_)
        context = matrix_desc(CTXT_)
        call BLACS_GRIDINFO(context, nr_proc_rows, nr_proc_cols, &
                            my_proc_row, my_proc_col)
        start_row = my_proc_row*row_block
        row_incr = nr_proc_rows*row_block
        start_col = my_proc_col*col_block
        col_incr = nr_proc_cols*col_block
        local_row = 1
        allocate(buffer(cols), stat=istat)
        if (istat /= 0) then
            print 5001, my_proc_row, my_proc_col, 8*cols
            5001 format(1X, '(', I3, ',', I3, ') can not allocate ', I12, &
                        ' bytes for buffer in write_matrix')
            call MPI_ABORT(MPI_COMM_WORLD, istat)
        end if
        call MPI_FILE_OPEN(MPI_COMM_WORLD, trim(out_file), &
                           MPI_MODE_WRONLY + MPI_MODE_CREATE, &
                           MPI_INFO_NULL, file_pointer, ierror)
        if (ierror /= 0) then
            print *, 'error opening file to write'
            call MPI_ABORT(MPI_COMM_WORLD, ierror)
        end if
        do row = start_row, rows, row_incr
            row_size = min(row_block, rows - row)
            do i = 1, row_size
                local_col = 1
                do col = start_col, cols, col_incr
                    buffer_size = min(col_block, cols - col)
                    pos = 8_LONG*((row + i - 1)*cols + col)
                    call set_file_pos(file_pointer, pos, ierror)
                    if (ierror /= 0) then
                        print 5002, my_proc_row, my_proc_col, pos, &
                                    file_pointer
                        5002 format(1X, 'error seek file in [', &
                                    I3, ', ', I3, ']', ' at ', &
                                    I10, ' fp ', I10)
                        call MPI_ERROR_STRING(ierror, error_str, &
                                              error_str_len, jerror)
                        print *, ierror, trim(error_str)
                        call MPI_ABORT(MPI_COMM_WORLD, ierror)
                    end if
                    do j = 1, buffer_size
                        buffer(j) = local_matrix(local_row, local_col + j - 1)
                    end do
                    call MPI_FILE_READ(file_pointer, buffer, buffer_size, &
                                       MPI_DOUBLE_PRECISION, status, ierror)
                    if (ierror /= 0) then
                        print 5003, my_proc_row, my_proc_col, pos, &
                                    buffer_size
                        5003 format(1X, 'error writing in [', &
                                    I3 ' x ', I3, '] at ' &
                                    I10, ' size ', I10)
                        call MPI_ERROR_STRING(ierror, error_str, &
                                              error_str_len, jerror)
                        print *, ierror, trim(error_str)
                        call MPI_ABORT(MPI_COMM_WORLD, ierror)
                    end if
                    local_col = local_col + buffer_size
                end do
                local_row = local_row + 1
            end do
        end do
        call MPI_FILE_CLOSE(file_pointer, ierror)
        deallocate(buffer)
        return
    end subroutine write_matrix

    integer function g_to_l_coord(block_len, nr_procs, g_i)
        integer, intent(in) :: block_len, nr_procs, g_i
        integer :: remainder, nr_blocks
        nr_blocks = (g_i - 1)/(nr_procs*block_len)
        remainder = mod(g_i - 1, block_len) + 1
        g_to_l_coord = nr_blocks*block_len + remainder
    end function g_to_l_coord

    logical function is_mine(block_len, nr_procs, my_proc, g_i)
        integer, intent(in) :: block_len, nr_procs, my_proc, g_i
        integer :: nr_blocks
        nr_blocks = (g_i - 1)/block_len
        is_mine = my_proc == mod(nr_blocks, nr_procs)
    end function is_mine

end module blacs_matrices
