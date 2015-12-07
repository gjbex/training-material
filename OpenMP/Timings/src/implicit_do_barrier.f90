program implicit_do_barrier
use, intrinsic :: iso_fortran_env, only : dp => REAL64, &
                                          error_unit, output_unit
use :: omp_lib
implicit none
real(kind=dp), dimension(:, :), allocatable :: matrix
integer :: iter_nr, nr_iters, matrix_dim, i, j
character(len=1024) :: buffer
real(kind=dp) :: wtime

call init_parameters(matrix_dim, nr_iters)
call init_matrix(matrix, matrix_dim)
if (size(matrix, 1) <= 5) &
    call print_matrix('initial', matrix)
wtime = omp_get_wtime()
!$omp parallel
do iter_nr = 1, nr_iters
    !$omp do private(j)
    do j = 1, matrix_dim
        do i = j, matrix_dim
            matrix(i, j) = erf(matrix(i, j))
        end do
    end do
    !$omp end do
end do
!$omp end parallel
wtime = omp_get_wtime() - wtime
write (unit=output_unit, fmt='(A, F10.6)') &
    'walltime implicit barrier = ', wtime

wtime = omp_get_wtime()
!$omp parallel
do iter_nr = 1, nr_iters
    !$omp do private(j)
    do j = 1, matrix_dim
        do i = j, matrix_dim
            matrix(i, j) = erf(matrix(i, j))
        end do
    end do
    !$omp end do nowait
end do
!$omp end parallel
wtime = omp_get_wtime() - wtime
write (unit=output_unit, fmt='(A, F10.6)') &
    'walltime nowait = ', wtime
if (size(matrix, 1) <= 5) &
    call print_matrix('final', matrix)

contains

    subroutine init_parameters(matrix_dim, nr_iters)
        implicit none
        integer, intent(out) :: matrix_dim, nr_iters
        if (command_argument_count() == 2) then
            call get_command_argument(1, buffer)
            read (buffer, '(I10)') matrix_dim
            call get_command_argument(2, buffer)
            read (buffer, '(I10)') nr_iters
        else
            matrix_dim = 1000
            nr_iters = 10
        end if
    end subroutine init_parameters

    subroutine init_matrix(matrix, n)
        implicit none
        real(kind=dp), dimension(:, :), allocatable, intent(out) :: matrix
        integer, intent(in) :: n
        integer :: ierr
        allocate(matrix(n, n), stat=ierr)
        if (ierr /= 0) then
            write (error_unit, '(A, I0, A, I0, A)') 'can not allocate ', &
                n, ' x ', n, ' matrix'
            stop
        end if
        call random_number(matrix)
    end subroutine init_matrix

    subroutine print_matrix(label, matrix)
        implicit none
        character(len=*), intent(in) :: label
        real(kind=dp), dimension(:, :), intent(in) :: matrix
        integer :: row_nr
        character(len=50) :: fmt_str
        write (fmt_str, "('(', I0, '(E12.3))')") size(matrix, 2)
        write (output_unit, '(A)') label
        do row_nr = 1, size(matrix, 1)
            write (output_unit, fmt_str) , matrix(row_nr, :)
        end do
    end subroutine print_matrix

end program implicit_do_barrier
