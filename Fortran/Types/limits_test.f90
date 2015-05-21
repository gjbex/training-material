program limits_test
    use, intrinsic :: iso_fortran_env, only : INT8, INT16, INT32, INT64, &
                                              REAL32, REAL64, REAL128 
    implicit none
    integer(kind=INT8) :: i8
    integer(kind=INT16) :: i16
    integer(kind=INT32) :: i32
    integer(kind=INT64) :: i64
    real(kind=REAL32) :: x32
    real(kind=REAL64) :: x64
    real(kind=REAL128) :: x128
    
    print '(A)', 'integer:'

    print '(A)', 'huge'
    print *, huge(i8)
    print *, huge(i16)
    print *, huge(i32)
    print *, huge(i64)

    print '(A)', 'digits'
    print *, digits(i8)
    print *, digits(i16)
    print *, digits(i32)
    print *, digits(i64)

    print '(A)', 'range'
    print *, range(i8)
    print *, range(i16)
    print *, range(i32)
    print *, range(i64)

    print '(A)', 'real:'

    print '(A)', 'huge:'
    print *, 32, huge(x32)
    print *, 64, huge(x64)
    print *, 128, huge(x128)

    print '(A)', 'tiny:'
    print *, 32, tiny(x32)
    print *, 64, tiny(x64)
    print *, 128, tiny(x128)

    print '(A)', 'epsilon:'
    print *, 32, epsilon(x32)
    print *, 64, epsilon(x64)
    print *, 128, epsilon(x128)

    print '(A)', 'range:'
    print *, 32, range(x32)
    print *, 64, range(x64)
    print *, 128, range(x128)

    print '(A)', 'minexponent:'
    print *, 32, minexponent(x32)
    print *, 64, minexponent(x64)
    print *, 128, minexponent(x128)

    print '(A)', 'maxexponent:'
    print *, 32, maxexponent(x32)
    print *, 64, maxexponent(x64)
    print *, 128, maxexponent(x128)

    print '(A)', 'precision:'
    print *, 32, precision(x32)
    print *, 64, precision(x64)
    print *, 128, precision(x128)

    print '(A)', 'digits:'
    print *, 32, digits(x32)
    print *, 64, digits(x64)
    print *, 128, digits(x128)

end program limits_test
