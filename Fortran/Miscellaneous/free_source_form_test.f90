PROGRAM free_source_form_test
    INTEGER :: i
    INTEGER, PARAMETER :: n = 10
    REAL :: x, y, z

    ! This will print something to screen
    DO I = 1, n
        print '(A, I2, A, I2)', 'This is iteration ', I,    &
                                 ' out of ', n
    END DO
    x = 3; y = 5; z = 7
    print *, x, y, z

END PROGRAM free_source_form_test
