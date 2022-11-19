cmake_minimum_required(VERSION 3.24)
project(serial C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "-O3")

include_directories(.)

add_executable(serial
        fft.c)

target_link_libraries(serial PRIVATE m)
