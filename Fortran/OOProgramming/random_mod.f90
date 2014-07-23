module random_mod
    implicit none
    private
    public :: init_random_seed

contains

    subroutine init_random_seed()
        implicit none
        integer :: seed_dim, clock, i
        integer, dimension(:), allocatable :: seed
        call random_seed(size=seed_dim)
        allocate(seed(seed_dim))
        call system_clock(count=clock)
        seed = clock + 37*[ (i - 1, i = 1, seed_dim) ]
        call random_seed(put=seed)
        deallocate(seed)
    end subroutine init_random_seed

end module random_mod

