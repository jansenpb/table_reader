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

        subroutine query_interface(T_ptr, Zq_, Hq_, Vq_, T_, Yf_, Yo_, Yp_) bind(C, name="query_interface")
            import
            type(C_ptr), value         :: T_ptr
            real(C_double), value      :: Zq_
            real(C_double), value      :: Hq_
            real(C_double), value      :: Vq_
            real(C_double)             :: T_
            real(C_double)             :: Yf_
            real(C_double)             :: Yo_
            real(C_double)             :: Yp_
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

        subroutine query(T_ptr, Zq_, Hq_, Vq_, T_, Yf_, Yo_, Yp_)
            type(C_ptr)     , intent(in) :: T_ptr
            double precision, intent(in) :: Zq_
            double precision, intent(in) :: Hq_
            double precision, intent(in) :: Vq_
            double precision, intent(out) :: T_ 
            double precision, intent(out) :: Yf_
            double precision, intent(out) :: Yo_
            double precision, intent(out) :: Yp_

            call query_interface(T_ptr, Zq_, Hq_, Vq_, T_, Yf_, Yo_, Yp_)

        end subroutine query

    !============================================================================

end module table_module
