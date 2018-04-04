program float_equal
    implicit none
    if (sqrt(2.0)*sqrt(2.0) == 2.0) then
        print '(A)', 'hooray!'
    else
        print '(A)', 'oops!'
    end if
end program float_equal
