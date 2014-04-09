program pure_fortran
implicit none

interface
    subroutine init_matrix(m)
        real(kind=8), allocatable, dimension(:,:), intent(inout) :: m
    end subroutine init_matrix
end interface

integer :: n, i, j
real(kind=8), allocatable, dimension(:,:) :: a, b, c
character(len=1024) :: argv
real :: start_time, end_time

if (command_argument_count() > 0) then
    call get_command_argument(1, argv)
    read (argv, fmt=*), n
else
    n = 5
end if

print *, "initializing a..."
call cpu_time(start_time)
allocate(a(n, n))
call init_matrix(a)
call cpu_time(end_time)
print *, "initialized a: ", end_time - start_time
print *, "initializing b..."
call cpu_time(start_time)
allocate(b(n, n))
call init_matrix(b)
call cpu_time(end_time)
print *, "initialized b: ", end_time - start_time
allocate(c(n, n))
print *, "multiplying..."
call cpu_time(start_time)
call dgemm('N', 'N', n, n, n, 1.0D00, a, n, b, n, 0.0D00, c, n)
call cpu_time(end_time)
print *, "multiplied: ", end_time - start_time


deallocate(a)
deallocate(b)
deallocate(c)

end program pure_fortran

subroutine init_matrix(m)
    implicit none
    real(kind=8), allocatable, dimension(:,:), intent(inout) :: m
    integer :: n, i, j
    real(kind=8) :: r
    n = size(m, 1)
    do j = 1, n
        do i = 1, n
            call random_number(r)
            m(i, j) = 5
        end do
    end do
end subroutine init_matrix

