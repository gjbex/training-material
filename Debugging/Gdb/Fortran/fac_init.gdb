# let's have a look at the code
b main
r
l
l fac_mod::factorial

# set breakpoint in factorial function, run
b fac_mod::factorial
c

# look around at breakpoint
p fac
b 16
p fac

# show stack frames, and move up to main, list
bt
frame 1
l

# set conditional breakpoint in body of doo loop
# into the function
b 6 if i .eq. 3

# show breakpoints, and remove the breakpoints in the factorial
# function
i b
d 2 3

# continue till conditional breakpoint in do loop, and step into
# function
c
s

# print function argument and fac value
p n
p fac

# set watchpoint on fac, and continue
watch fac
c

# watchpoint is hit before the do-loop in factorial starts,
# so fac is initialized automatically with an "unexpected"
# value; normal Fortran semantics for a procedure variable
# that is initialized on declaration


# edit the fac_mod.f90 from within GDB, make and run
# edit fac_mod::factorial
# make
# d
# r

# now all results are correct, so quit

# q
