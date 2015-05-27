Ring
====

A few examples of point-to-point communication.

What is it?
-----------
1. `unidirectional.f90`: message is send around a ring, serial execution
    due to send/receive order
1. `async.f90`: example of non-blocking send, normal receive.
1. `deadlock.f90`: code that can result in a deadlock, depending on
    the communication method chosen by the implementation.
