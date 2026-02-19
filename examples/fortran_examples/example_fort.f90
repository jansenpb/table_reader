program example_fort

    use table_module

    use, intrinsic :: ISO_C_Binding, only: C_ptr, C_double, C_char

    implicit none

    !=============================================================

    !-------------------------------------------------------------

    type(C_ptr) :: T_ptr

    real(C_double) :: T 
    real(C_double) :: Yf 
    real(C_double) :: Yo 
    real(C_double) :: Yp

    double precision :: Z = 0.04
    double precision :: H = 0.3
    double precision :: V = 0.5
    
    
    character(len=28) :: filename = "../../cfd_lookup_table_3d.h5"
    
    call Table(T_ptr, filename)

    call query(T_ptr, Z, H, V, T, Yf, Yo, Yp)

    write(*,*) "Temp (K)   = ", T
    write(*,*) "Y_Fuel     = ", Yf
    write(*,*) "Y_Oxidizer = ", Yo 
    write(*,*) "Y_Products = ", Yp

end program example_fort
