PROGRAM syntax_error
    IMPLICIT none
    USE, INTRINSIC :: iso_fortran_env, ONLY : output_unit
    WRITE (UNIT=output_unit, FMT='(A)') 'hello world'
    END PROGRAM syntax_error

