program deadlock
      use, intrinsic :: iso_fortran_env, only : error_unit
      use :: mpi_f08
      implicit none
      integer, parameter :: tag = 17
      integer :: my_rank, my_size, partner, sbuff, rbuff

      call MPI_Init()
      call MPI_Comm_size(MPI_COMM_WORLD, my_size)
      if (my_size < 2) then
          write (unit=error_unit, fmt='(A)') &
              '### error: must run with at least two processes'
          call MPI_Abort(MPI_COMM_WORLD, 1)
      end if
      call MPI_Comm_rank(MPI_COMM_WORLD, my_rank)
      sbuff = my_rank
      partner = mod(my_rank + 1, 2)
      print '("rank ", I0, " partners with ", I0)', my_rank, partner
      if (my_rank == 0) then
          call MPI_Ssend(sbuff, 1, MPI_INTEGER, partner, tag, &
                         MPI_COMM_WORLD)
          call MPI_Recv(rbuff, 1, MPI_INTEGER, partner, tag, &
                        MPI_COMM_WORLD, MPI_STATUS_IGNORE)
      else if (my_rank == 1) then
          call MPI_Ssend(sbuff, 1, MPI_INTEGER, partner, tag, &
                         MPI_COMM_WORLD)
          call MPI_Recv(rbuff, 1, MPI_INTEGER, partner, tag, &
                        MPI_COMM_WORLD, MPI_STATUS_IGNORE)
      end if
      print '("rank ", I0, " received ", I0)', my_rank, rbuff
      call MPI_Finalize()
end program deadlock
