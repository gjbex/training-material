module utils_mod

contains

    subroutine get_file_name(file_name)
        use, intrinsic :: iso_fortran_env, only : error_unit
        implicit none
        character(len=*), intent(out) :: file_name
        character(len=1024) :: argv
        if (command_argument_count() < 1) then
            write (unit=error_unit, fmt="(A)") "# error: no file name given"
            stop
        end if
        call get_command_argument(1, argv)
        file_name = trim(argv)
    end subroutine get_file_name

    subroutine get_dataset_name(dataset_name)
        use, intrinsic :: iso_fortran_env, only : error_unit
        implicit none
        character(len=*), intent(out) :: dataset_name
        character(len=1024) :: argv
        if (command_argument_count() < 2) then
            write (unit=error_unit, fmt="(A)") &
                "# error: no dataset name given"
            stop
        end if
        call get_command_argument(2, argv)
        dataset_name = trim(argv)
    end subroutine get_dataset_name

    subroutine get_block_size(block_size)
        use, intrinsic :: iso_fortran_env, only : error_unit
        implicit none
        integer, intent(out) :: block_size
        character(len=1024) :: argv
        if (command_argument_count() < 3) then
            write (unit=error_unit, fmt="(A)") &
                "# error: no block size given"
            stop
        end if
        call get_command_argument(3, argv)
        read (argv, "(I10)") block_size
    end subroutine get_block_size

end module utils_mod
