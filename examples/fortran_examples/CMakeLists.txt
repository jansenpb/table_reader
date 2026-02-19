if(CMAKE_Fortran_COMPILER AND BUILD_FORTRAN_INTERFACE)
    set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")

    add_executable(example_fort.x example_fort.f90)
    target_include_directories(example_fort.x PRIVATE "${CMAKE_BINARY_DIR}/src/fortran_wraps")
    target_link_libraries(example_fort.x PRIVATE read_table read_table_fortran -fPIC)
    install(TARGETS example_fort.x DESTINATION "${CMAKE_CURRENT_SOURCE_DIR}")

elseif(!CMAKE_Fortran_COMPILER AND BUILD_FORTRAN_INTERFACE)

    message([FATAL ERROR] "No Fortran compiler found")

endif()


