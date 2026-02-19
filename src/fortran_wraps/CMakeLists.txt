if (CMAKE_Fortran_COMPILER AND BUILD_FORTRAN_INTERFACE)

    add_library(read_table_fortran)
    add_library(read_table_fortran::read_table_fortran ALIAS read_table_fortran)

    target_sources(read_table_fortran PRIVATE table_module.f90 c_interface.cc)

    target_link_libraries(read_table_fortran read_table)
    target_include_directories(read_table_fortran PRIVATE "${CMAKE_SOURCE_DIR}")

    ############## Install Library #######################

    include(GNUInstallDirs)

    install(FILES "${CMAKE_BINARY_DIR}/src/fortran_wraps/table_module.mod"
            DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}")

    install(TARGETS read_table_fortran
            EXPORT  read_table_fortran_exp)

    install(EXPORT   read_table_fortran_exp
            FILE     read_table_fortran_exp.cmake
            NAMESPACE read_table_fortran::
            DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/read_table_fortran")

    install(FILES   "read_table_fortranConfig.cmake"
            DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/read_table_fortran")

else()
    message([FATAL ERROR] "No Fortran Compiler found")
endif()

