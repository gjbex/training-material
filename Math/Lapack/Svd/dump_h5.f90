program dump_h5
use utils_mod, only : get_file_name, get_dataset_name
use matrix_mod, only : read_matrix, print_matrix
use, intrinsic :: iso_fortran_env, only : dp => REAL64, error_unit
implicit none
real(kind=dp), allocatable, dimension(:, :) :: matrix
character(len=1024) :: file_name, dataset_name

call get_file_name(file_name)
call get_dataset_name(dataset_name)
call read_matrix(file_name, dataset_name, matrix)
call print_matrix(matrix)

end program dump_h5
