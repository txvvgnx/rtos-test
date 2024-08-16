cmake_minimum_required(VERSION 3.20)

project("rtos-test" C CXX ASM)

include(cmake/st-project.cmake)

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -u _printf_float")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -u _scanf_float")

add_executable(${PROJECT_NAME})
add_st_target_properties(${PROJECT_NAME})
