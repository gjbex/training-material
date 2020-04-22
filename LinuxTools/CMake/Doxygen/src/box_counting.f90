!> @brief application to perform box counting to estiamte the fractal
!>        dismension of an 2D object
!>
!> The application assumes that the 2D is in a unit square defined by
!> the points (0, 0), (1, 0), (0, 1), (1, 1).  A command line argument
!> specifies the resolution of the boxes, e.g., 2 means that 4 boxes
!> are used, 8 would mean 64 boxes.
!> Data is read from standard input in the form of x,y-coordinates in
!> the interval [0.0, 1.0].
!>
program box_counting
    use, intrinsic :: iso_fortran_env, only : error_unit, iostat_end, &
                                              DP => REAL64
    implicit none
    real(kind=DP) :: delta, x, y, numerator, denominator
    integer, dimension(:, :), allocatable :: counts
    integer :: nr_edges, istat, nr_non_empty

    ! get command line argument
    nr_edges = get_nr_edges()
    delta = 1.0_DP/nr_edges

    ! allocate the counts 2D array
    allocate(counts(nr_edges, nr_edges), stat=istat)
    if (istat /= 0) then
        write (unit=error_unit, fmt='(A)') &
            'Can not allocate counts'
        stop 2
    end if
    counts = 0

    ! read points and count
    do
        call get_coordinates(x, y, istat)
        if (istat == iostat_end) exit
        call box_count(counts, delta, x, y)
    end do

    ! display result
    nr_non_empty = count_non_empty(counts)
    numerator = log(real(nr_non_empty, kind=DP))
    denominator = log(real(nr_edges, kind=DP))
    print '(I7, 4E15.7)', nr_edges, delta, numerator, denominator, &
        numerator/denominator

    ! clean up
    deallocate(counts)

contains

    !> @brief validate command line argument and returns value of the
    !>        number of edges
    !> @returns number of edges
    function get_nr_edges() result(nr_edges)
        use, intrinsic :: iso_fortran_env, only : error_unit
        implicit none
        integer :: nr_edges
        character(len=1024) :: buffer, msg
        integer :: istat

        if (command_argument_count() /= 1) then
            write (unit=error_unit, fmt='(A)') &
                'error: expecting number of edges to define boxes'
            stop 1
        end if
        call get_command_argument(1, buffer)
        read (buffer, fmt=*, iostat=istat, iomsg=msg) nr_edges
        if (istat /= 0) then
            write (unit=error_unit, fmt='(2A)') &
                'error: ', msg
            stop 1
        end if
        if (nr_edges < 1) then
            write (unit=error_unit, fmt='(A)') &
                'error: number of edges is at least 1'
            stop 1
        end if
    end function get_nr_edges

    !> @brief read x, y coordinates from standard input
    !> @param[out] x coordinate
    !> @param[out] y coordinate
    !> @param[out] istat is 0 upon succesful read, `iostat_end` when
    !>             no input remains
    subroutine get_coordinates(x, y, istat)
        use, intrinsic :: iso_fortran_env, only : input_unit, error_unit
        implicit none
        real(kind=DP), intent(out) :: x, y
        integer, intent(out) :: istat
        character(len=1024) :: msg

        read (unit=input_unit, fmt=*, iostat=istat, iomsg=msg) x, y
        if (istat == iostat_end) return
        if (istat /= 0) then
            write (unit=error_unit, fmt='(2A)') &
                'error: ', msg
            stop 3
        end if
    end subroutine get_coordinates

    !> @brief update the box counts for the given coordinates
    !> @param[inout] counts the points in each of the boxes
    !> @param[in] delta is the length of the side of a box
    !> @param[in] x coordinate of the new point
    !> @param[in] y coordinate of the new point
    subroutine box_count(counts, delta, x, y)
        implicit none
        integer, dimension(:, :), intent(inout) :: counts
        real(kind=DP), intent(in) :: delta, x, y
        integer :: i, j

        i = 1 + int(x/delta)
        j = 1 + int(y/delta)
        ! if x or y is exactly equalt to 1, we lump it into the last box
        if (i > size(counts, 1)) i = i - 1
        if (j > size(counts, 1)) j = j - 1
        counts(i, j) = counts(i, j) + 1
    end subroutine box_count

    !> @brief return the number of boxes that have a non-zero count
    !> @param[in] counts of the boxes
    !> @returns the number of boxes with a non-zero count
    function count_non_empty(counts) result(nr_non_empty)
        implicit none
        integer, dimension(:, :), intent(in) :: counts
        integer :: nr_non_empty

        nr_non_empty = size(counts) - count(counts == 0)
    end function count_non_empty

end program box_counting
