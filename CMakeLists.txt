cmake_minimum_required(VERSION 3.17)
project(SC_Solver C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(SC_Solver
        main.c
        main.h
        main_func.c)
