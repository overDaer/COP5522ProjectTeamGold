cmake_minimum_required(VERSION 3.24)
project(fft_serial C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "-O3")

include_directories(.)

add_executable(fft_serial
        fft_serial.c
        fft.h
        fft.c)

target_link_libraries(fft_serial PRIVATE m)
