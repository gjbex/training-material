Ring
====

A few examples of point-to-point communication.

What is it?
-----------
1. `unidirectional.f90`: message is send around a ring, serial execution
    due to send/receive order.  Note that this may deadlock for `np=1`,
    depending on whether blocking or non-blocking communication is choosen
    by the  compiler/runtime.
1. `nonbloking.f90`: example of non-blocking send, normal receive.
1. `nonbloking_f08.f90`: example of non-blocking send, normal receive,
    but using Fortran 2008 interface.
1. `deadlock.f90`: code that can result in a deadlock, depending on
    the communication method chosen by the implementation.
1. `bidirectional.f90': bidirectional "halo exchange" using non-blocking
    point-to-point communication.
1. `sendrecv.f90': bidirectional "halo exchange" using send-receive
    point-to-point communication.
1. `cart_sendrecv.f90': bidirectional "halo exchange" using send-receive
    point-to-point communication, neighbours on 1D Carthesian grid, found
    using shift operation.
1. `cart_sendrecv_f08.f90': bidirectional "halo exchange" using
    send-receive point-to-point communication, neighbours on 1D Carthesian
    grid, found using shift operation using Fortran 2008 interface.
1. `torus.f90`: 2D torus topology using a Carthesian communicator and
    `MPI_Sendrecv' for halo exchange.
1. `one_sided.f90`: each process puts a value into its right neighbour,
    and gets a message from that neighbour using one-sided communication.
1. `bidirectional_request_array.c`: illustration of using `MPI_Waitall`.
