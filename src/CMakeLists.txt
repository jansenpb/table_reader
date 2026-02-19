############### Table Reader Library ########################

add_library(read_table SHARED)
add_library(read_table::read_table ALIAS read_table)

target_sources(read_table
    PRIVATE
        table_reader.cc
    PUBLIC
    FILE_SET read_table_headers
        TYPE HEADERS 
        BASE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}"
        FILES table_reader.h
)

############## Build Library ################################

find_package(HighFive REQUIRED)

target_include_directories(read_table PRIVATE "/Users/jansenpb/codes/HighFive/include")
target_include_directories(read_table PRIVATE "/opt/homebrew/opt/hdf5/include")
target_link_libraries(read_table HighFive)

#############################################################

include(GNUInstallDirs)

install(
    TARGETS read_table                           # install Library
    EXPORT  read_table_exp                       # define export variable for next command
    FILE_SET read_table_headers DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}")


install(
    EXPORT read_table_exp 
    FILE   read_table_exp.cmake 
    NAMESPACE read_table::
    DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/read_table"
)

install(
    FILES "read_tableConfig.cmake"                           # install config files 
    DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/read_table"   # edit file read_tableConfig.cmake 
)
