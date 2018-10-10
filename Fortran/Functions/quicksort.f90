program quicksort
      implicit none
      integer, parameter :: n = 10
      real, dimension(:), allocatable :: values
      character(len=10) :: fmt_str

      write (fmt_str, '(A, I0, A)') '(', n, 'F8.5)'
      call init_values(values, n)
      print fmt_str, values
      call qsort(values)
      print fmt_str, values

contains

      subroutine init_values(values, n)
          implicit none
          real, dimension(:), allocatable, intent(inout) :: values
          integer, intent(in) :: n
          allocate(values(n))
          call random_number(values)
      end subroutine init_values

      recursive subroutine qsort(values)
          implicit none
          real, dimension(:), intent(inout) :: values
          call qsort_r(values, 1, size(values))
      end subroutine qsort

      recursive subroutine qsort_r(values, low, high)
          implicit none
          real, dimension(:), intent(inout) :: values
          integer, intent(in) :: low, high
          integer :: pivot
          if (low < high) then
              pivot = find_pivot(values, low, high)
              call qsort_r(values, low, pivot - 1)
              call qsort_r(values, pivot, high)
          end if
      end subroutine qsort_r

      subroutine swap_values(values, i, j)
          implicit none
          real, dimension(:), intent(inout) :: values
          integer, intent(in) :: i, j
          real :: tmp
          tmp = values(i)
          values(i) = values(j)
          values(j) = tmp
      end subroutine swap_values

      function find_pivot(values, low, high) result(pivot)
          implicit none
          real, dimension(:), intent(inout) :: values
          integer, intent(in) :: low, high
          integer :: pivot
          real :: pivot_value
          integer :: i
          pivot_value = values(high)
          pivot = low
          do i = low, high - 1
              if (values(i) < pivot_value) then
                  call swap_values(values, i, pivot)
                  pivot = pivot + 1
              end if
          end do
          call swap_values(values, pivot, high)
      end function find_pivot

end program quicksort
