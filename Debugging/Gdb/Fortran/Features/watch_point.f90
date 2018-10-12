program watch_point
      implicit none
      integer, parameter :: x_max = 4, y_max = 5, t_max = 100
      real, parameter :: prob = 0.7, boundary  = 0.0
      real, dimension(x_max, y_max) :: temp
      integer :: t

      call init_temp(temp, boundary)
      call show_temp(temp)
      do t = 1, t_max
          call update_temp(temp)
          call perturb_temp(temp, prob)
      end do
      call show_temp(temp)

contains

      subroutine init_temp(temp, boundary)
          implicit none
          real, dimension(:, :), intent(inout) :: temp
          real, intent(in) :: boundary
          integer :: i
          call random_number(temp)
          do i = 1, size(temp, 1)
              temp(i, 1) = boundary
              temp(i, shape(temp, 2)) = boundary
          end do
          do i = 1, size(temp, 2)
              temp(1, i) = boundary
              temp(shape(temp, 1), i) = boundary
          end do
      end subroutine init_temp

      subroutine update_temp(temp)
          implicit none
          real, dimension(:, :), intent(inout) :: temp
          integer :: i, j
          do j = 2, size(temp, 2) - 1
              do i = 2, size(temp, 1) - 1
                  temp(i, j) = 0.25*(temp(i - 1, j) + &
                                     temp(i + 1, j) + &
                                     temp(i,  j - 1) + &
                                     temp(i, j + 1))
              end do
          end do
      end subroutine update_temp

      subroutine perturb_temp(temp, prob)
          implicit none
          real, dimension(:, :), intent(inout) :: temp
          real, intent(in) :: prob
          integer :: i, j
          real :: r
          call random_number(r)
          if (r > prob) then
              call random_number(r)
              i = 1 + int(r*size(temp, 1))
              call random_number(r)
              j = 1 + int(r*size(temp, 2))
              call random_number(r)
              temp(i, j) = r
          end if
      end subroutine perturb_temp

      subroutine show_temp(temp)
          implicit none
          real, dimension(:, :), intent(inout) :: temp
          integer :: i
          character(len=32) :: fmt_str
          write (fmt_str, '(A, I0, A)') '(', size(temp, 2), 'ES15.5)'
          do i = 1, size(temp, 1)
              print fmt_str, temp(i, :)
          end do
      end subroutine show_temp

end program watch_point
