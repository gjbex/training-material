# file matrix multiplyexe

# This application times a naive matrix-matrix multiplication
#  using CPU_TIME, and reports a value that is an order of
# magnitude too large.

# $ make clean all`
#`$ time ./matrix_multiply.exe

# note that the reported time is off by an order of magnitude.

# set a breakpoint after the statement measuring the start and
# end time
b 19
b 31

# run till first breakpoint, and show start time
r
p tic

# continue till the next breakpoint, and show both start
# and end time
c
p tic
p toc

# print time difference
p dt

# proceed until value is printed
n
n

# clearly the problem is with the output, not the value, output
# format is wrong.

# The following steps have to be done interactively
# edit matrix_multiply.f90:32

# Change `1pes` to `e`

# make and run the progam again
# make
# r

# now the timing printed is correct is correct, quit
# q

