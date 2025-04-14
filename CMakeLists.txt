cmake_minimum_required(VERSION 3.20)
project(llir)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED true)
add_executable(llir main.cpp libcmdline/libcmdline.c)