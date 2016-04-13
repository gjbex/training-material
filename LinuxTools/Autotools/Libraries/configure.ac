AC_INIT([cannon_ode], [1.0], [geertjan.bex@uhasselt.be])
AM_INIT_AUTOMAKE([-Wall -Werror foreign tar-pax])

# C compiler
AC_PROG_CC

standard headers
AC_CHECK_HEADERS([err.h stdio.h])

# math library
AC_CHECK_HEADERS([math.h])
AC_SEARCH_LIBS([sqrt], [m], [],
               [AC_MSG_ERROR([unable to find log10 function])])

# hiredis library
PKG_CHECK_MODULES([gsl], [gsl])
AC_CHECK_HEADERS([gsl/gsl_errno.h gsl/gsl_odeiv2.h])
# AC_SEARCH_LIBS([gsl_odeiv2_driver_apply], [gsl], [], [])

AC_CONFIG_FILES([
    Makefile
    src/Makefile
])
AC_OUTPUT
