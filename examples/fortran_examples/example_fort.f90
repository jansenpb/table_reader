program example_fort

    use table_module

    use, intrinsic :: ISO_C_Binding, only: C_ptr, C_double, C_char

    implicit none

    !=============================================================

    !-------------------------------------------------------------

    type(C_ptr) :: T_ptr

    real(C_double) :: T_q
    real(C_double), allocatable, dimension(:) :: Y_species


    double precision :: Z = 0.055
    double precision :: V = 0.2
    double precision :: H = 100
    double precision :: M0= 1e12
    integer          :: n_species, i 
    character(len=32) :: s_name
    
    character(len=28) :: filename = "../../cfd_lookup_table_4d.h5"
    
    call Table(T_ptr, filename)

    call get_num_species(T_ptr, n_species)
    allocate(Y_species(n_species))

    call query(T_ptr, Z, V, H, M0, Y_species, T_q)

    write(*,*) "Temp (K) = ", T_q 
    do i=1, min(n_species, 5)
        call get_species_name(T_ptr, i, s_name)
        write(*,*) "Y_", trim(s_name), " = ", Y_species(i)
    enddo 

end program example_fort
