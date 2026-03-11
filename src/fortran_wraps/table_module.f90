module table_module

    use, intrinsic :: ISO_C_Binding, only: C_double, C_ptr, C_char

    implicit none

    private

    !=============================================================
    ! declare the C interface

    interface

        !--------- Upload the table ------------------------------

        function Table_Interface(filename) result(T_ptr) bind(C, name="Table_Interface") 
            import
            type(C_ptr)              :: T_ptr
            character(C_char)        :: filename
        end function Table_Interface

        !--------- Query the table  ------------------------------

        subroutine query_interface(T_ptr, Zq_, Hq_, Vq_, Y_CH4_q, Y_O2_q, Y_CO2_q, Y_H2O_q, Y_CO_q, Y_OH_q, &
                Y_O_q, Y_H_q, Y_H2_q, Y_C2H2_q, Y_C6H6_q, Y_C_q, Y_N2_q, rad_q, edc_q, T_q) bind(C, name="query_interface")
            import
            type(C_ptr), value         :: T_ptr
            real(C_double), value      :: Zq_
            real(C_double), value      :: Hq_
            real(C_double), value      :: Vq_
            real(C_double)             :: Y_CH4_q
            real(C_double)             :: Y_O2_q
            real(C_double)             :: Y_CO2_q
            real(C_double)             :: Y_H2O_q
            real(C_double)             :: Y_CO_q
            real(C_double)             :: Y_OH_q
            real(C_double)             :: Y_O_q
            real(C_double)             :: Y_H_q
            real(C_double)             :: Y_H2_q
            real(C_double)             :: Y_C2H2_q
            real(C_double)             :: Y_C6H6_q
            real(C_double)             :: Y_C_q
            real(C_double)             :: Y_N2_q
            real(C_double)             :: rad_q
            real(C_double)             :: edc_q
            real(C_double)             :: T_q
        end subroutine query_interface

        !----------------------------------------------------------

    end interface

    !-------------------------------------------------------------------------

    public :: Table, query 

    !----------- Wrapper routines ---------------------------------

    contains 

        !---------------------------------------------

        subroutine Table(T_ptr, filename)
            type(C_ptr), intent(out) :: T_ptr
            character, intent(in)    :: filename

            T_ptr = Table_Interface(filename)
        end subroutine Table

        !---------------------------------------------

        subroutine query(T_ptr, Zq_, Hq_, Vq_, Y_CH4_q, Y_O2_q, Y_CO2_q, Y_H2O_q, Y_CO_q, &
                Y_OH_q, Y_O_q, Y_H_q, Y_H2_q, Y_C2H2_q, Y_C6H6_q, Y_C_q, Y_N2_q, rad_q, edc_q, T_q)
            type(C_ptr)     , intent(in) :: T_ptr
            double precision, intent(in) :: Zq_
            double precision, intent(in) :: Hq_
            double precision, intent(in) :: Vq_
            double precision, intent(out) :: Y_CH4_q 
            double precision, intent(out) :: Y_O2_q 
            double precision, intent(out) :: Y_CO2_q 
            double precision, intent(out) :: Y_H2O_q 
            double precision, intent(out) :: Y_CO_q 
            double precision, intent(out) :: Y_OH_q 
            double precision, intent(out) :: Y_O_q 
            double precision, intent(out) :: Y_H_q 
            double precision, intent(out) :: Y_H2_q 
            double precision, intent(out) :: Y_C2H2_q 
            double precision, intent(out) :: Y_C6H6_q 
            double precision, intent(out) :: Y_C_q 
            double precision, intent(out) :: Y_N2_q 
            double precision, intent(out) :: rad_q 
            double precision, intent(out) :: edc_q 
            double precision, intent(out) :: T_q 

            call query_interface(T_ptr, Zq_, Hq_, Vq_, Y_CH4_q, Y_O2_q, Y_CO2_q, Y_H2O_q, Y_CO_q, &
                Y_OH_q, Y_O_q, Y_H_q, Y_H2_q, Y_C2H2_q, Y_C6H6_q, Y_C_q, Y_N2_q, rad_q, edc_q, T_q)

        end subroutine query

    !============================================================================

end module table_module
