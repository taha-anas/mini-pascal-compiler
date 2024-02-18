cmake_minimum_required(VERSION 3.27)
project(Compila C)

set(CMAKE_C_STANDARD 17)

add_executable(Compila
        compiler.c
        compiler.h)
