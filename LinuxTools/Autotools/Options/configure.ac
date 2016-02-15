AC_INIT([hello_world], [1.0], [geertjan.bex@uhasselt.be])
AM_INIT_AUTOMAKE([-Wall -Werror foreign tar-pax])
AC_CONFIG_FILES([
    Makefile
    src/Makefile
])
AC_ARG_ENABLE(
    [openmp],
    AS_HELP_STRING(
        [--enable-openmp],
        [Enable compilatio with OpenMP support [default=no]]
    ),
    [case $enableval in
    yes|no) ;;
    *) AC_MSG_ERROR([bad value $enableval for --enable-openmp, need yes/no])
    esac],
    [enable_openmp=no]
)
AS_IF([test "x$enable_openmp" = "xyes"], [
    CFLAGS="$CFLAGS -fopenmp"
])
AC_PROG_CC(gcc)
AC_OUTPUT
