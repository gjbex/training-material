program rationals
use rationals_mod
implicit none
type(rational) :: a, b, c, d

a = rational(2, 3)
call rat_print(a)
b = rational(1, 5)
call rat_print(b)
d = a + b
call rat_print(d)
a = rational(1, 4)
b = rational(1, 4)
d = a + b
call rat_print(d)

a = rational(-2, 4)
b = rational(1, 4)
d = a + b
call rat_print(d)

a = rational(2, -4)
b = rational(1, 4)
d = a + b
call rat_print(d)

a = rational(2, -4)
b = rational(1, 4)
d = a*b
call rat_print(d)

a = rational(2, -4)
d = 3*a
call rat_print(d)

c = rational(3, 0)
call rat_print(c)

end program rationals
