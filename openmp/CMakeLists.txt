cmake_minimum_required(VERSION 3.24)
set(CMAKE_PROJECT_NAME  "fft_openmp")
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "-O3 -fopenmp")

project(${CMAKE_PROJECT_NAME} C)

include_directories(.)

add_executable(${CMAKE_PROJECT_NAME}
        fft_openmp.c
        fft.h
        fft.c
        microtime.c
        microtime.h)

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE m)
