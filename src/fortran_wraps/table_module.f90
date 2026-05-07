module table_module

    use, intrinsic :: ISO_C_Binding, only: C_double, C_ptr, C_char, C_int

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

        subroutine query_interface(T_ptr, Zq_, Vq_, Hq_, M0q_, Y_species_q, T_q) bind(C, name="query_interface")
            import
            type(C_ptr), value           :: T_ptr
            real(C_double), value        :: Zq_, Vq_, Hq_, M0q_
            real(C_double), dimension(*) :: Y_species_q
            real(C_double)               :: T_q
        end subroutine query_interface

        !----------------------------------------------------------

        subroutine get_num_species_interface(T_ptr, n) bind(C, name="get_num_species_interface")
            import
            type(C_ptr), value :: T_ptr
            integer(C_int)     :: n 
        end subroutine get_num_species_interface

        !----------------------------------------------------------

        subroutine get_species_name_interface(T_ptr, i, names, max_len) bind(C, name="get_species_name_interface")
            import
            type(C_ptr), value              :: T_ptr
            integer(C_int), value           :: i, max_len
            character(C_char), dimension(*) :: names
        end subroutine get_species_name_interface

    end interface

    !-------------------------------------------------------------------------

    public :: Table, query, get_num_species, get_species_name 

    !----------- Wrapper routines ---------------------------------

    contains 

        !---------------------------------------------

        subroutine Table(T_ptr, filename)
            type(C_ptr), intent(out) :: T_ptr
            character, intent(in)    :: filename

            T_ptr = Table_Interface(filename)
        end subroutine Table

        !---------------------------------------------

        subroutine query(T_ptr, Zq_, Vq_, Hq_, M0q_, Y_species_q, T_q)
            type(C_ptr)     , intent(in)                :: T_ptr
            double precision, intent(in)                :: Zq_, Vq_, Hq_, M0q_
            double precision, dimension(:), intent(out) :: Y_species_q
            double precision, intent(out)               :: T_q 

            call query_interface(T_ptr, Zq_, Vq_, Hq_, M0q_, Y_species_q, T_q)

        end subroutine query

        !--------------------------------------------

        subroutine get_num_species(T_ptr, n)
            type(C_ptr), intent(in) :: T_ptr
            integer, intent(out)    :: n 
            call get_num_species_interface(T_ptr, n)
        end subroutine get_num_species

        !--------------------------------------------

        subroutine get_species_name(T_ptr, i, names)
            type(C_ptr), intent(in) :: T_ptr
            integer, intent(in)     :: i 
            character(len=*), intent(out) :: names
            integer                       :: max_len

            max_len = len(names)
            call get_species_name_interface(T_ptr, i-1, names, max_len)
        end subroutine get_species_name

    !============================================================================

end module table_module
