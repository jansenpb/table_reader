program example_fort

    use table_module

    use, intrinsic :: ISO_C_Binding, only: C_ptr, C_double, C_char

    implicit none

    !=============================================================

    !-------------------------------------------------------------

    type(C_ptr) :: T_ptr

    real(C_double) :: Y_CH4_q, Y_O2_q, Y_CO2_q, Y_H2O_q, Y_CO_q, Y_OH_q, Y_O_q, Y_H_q, Y_H2_q, Y_C2H2_q, Y_C6H6_q, &
        Y_C_q, Y_N2_q, rad_q, edc_q, T_q

    double precision :: Z = 0.04
    double precision :: H = 0.3
    double precision :: V = 0.5
    
    
    character(len=28) :: filename = "../../cfd_lookup_table_3d.h5"
    
    call Table(T_ptr, filename)

    call query(T_ptr, Z, H, V, Y_CH4_q, Y_O2_q, Y_CO2_q, Y_H2O_q, Y_CO_q, &
                Y_OH_q, Y_O_q, Y_H_q, Y_H2_q, Y_C2H2_q, Y_C6H6_q, Y_C_q, Y_N2_q, rad_q, edc_q, T_q)

end program example_fort
