program logical_order
    use, intrinsic :: iso_fortran_env, only : dp => REAL64
    implicit none
    integer, parameter :: n = 10
    logical, parameter :: normalize = .true.
    real(kind=dp), dimension(n) :: x
    real(kind=dp) :: result
    integer :: i

    do i = 1, n
        x(i) = real(i*i, kind=dp)
    end do
    result = accumulate(x)
    print '(A, F10.1)', 'result, not normalized = ', result
    result = accumulate(x, normalize)
    print '(A, F10.1)', 'result, normalized = ', result

contains

    function accumulate(x, normalize) result(acc)
        implicit none
        real(kind=dp), dimension(:), intent(in) :: x
        logical, intent(in), optional :: normalize
        real(kind=dp) :: acc
        acc = sum(x)
        if (present(normalize) .and. normalize) then
            acc = acc/size(x)
        end if
    end function accumulate

end program logical_order

