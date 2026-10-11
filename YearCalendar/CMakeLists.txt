cmake_minimum_required(VERSION 4.2)

project(YearCalendar C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

if (WIN32)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -static -static-libgcc -static-libstdc++")
endif()

add_executable(YearCalendar YearSystemBody.c)