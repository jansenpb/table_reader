set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib") # to include read_table


#---------------------

add_executable(example driver.cc)
target_include_directories(read_table PRIVATE "${PROJECT_SOURCE_DIR}/src")
target_link_libraries(example PRIVATE read_table)
install(TARGETS example DESTINATION "${CMAKE_CURRENT_SOURCE_DIR}")

