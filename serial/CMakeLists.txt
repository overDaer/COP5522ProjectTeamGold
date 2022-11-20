cmake_minimum_required(VERSION 3.24)
project(fft_serial C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "-O3")

# Comment the line below to disable printing.
#set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -DDEBUG")

include_directories(.)

add_executable(fft_serial
        fft_serial.c
        fft.h
        fft.c
        microtime.c
        microtime.h)

target_link_libraries(fft_serial PRIVATE m)
