program buffer_size
      use :: mpi_f08
      implicit none
      integer, parameter :: corr_size = 10, root = 0
      integer, dimension(:), allocatable :: sbuff
      integer, dimension(corr_size) :: rbuff
      integer :: my_rank, my_size, buff_size, i

      call MPI_Init()

      call MPI_Comm_rank(MPI_COMM_WORLD, my_rank)
      call MPI_Comm_size(MPI_COMM_WORLD, my_size)

      if (my_rank == root + 1) then
          buff_size = corr_size
      else
          buff_size = corr_size
      end if
      print '("rank ", I0, ": size ", I0)', &
          my_rank, buff_size
      allocate(sbuff(buff_size))
      do i = 1, buff_size
          sbuff(i) = 10**my_rank + i
      end do

      if (my_rank /= root + 1) then
          call MPI_Reduce(sbuff, rbuff, buff_size, &
                          MPI_INTEGER, MPI_SUM, root, &
                          MPI_COMM_WORLD)
      else
          call MPI_Reduce(sbuff, rbuff, buff_size, &
                          MPI_CHARACTER, MPI_SUM, root, &
                          MPI_COMM_WORLD)
      end if

      if (my_rank == root) &
          print '(I0)', rbuff

      call MPI_Finalize()

end program buffer_size
