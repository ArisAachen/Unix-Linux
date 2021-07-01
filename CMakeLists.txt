cmake_minimum_required(VERSION 3.13)
project(Learn C)

set(CMAKE_C_STANDARD 99)
set(INCLUDE_DIRECTORIES /usr/include/glib-2.0)
include_directories(includes_folder)

add_executable(glic_test glib_test.c)