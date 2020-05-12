cmake_minimum_required(VERSION 3.16)
project(jahresprojekt C)

set(CMAKE_C_STANDARD 99)
include_directories(src)

add_executable(sudoku src/main.c)
add_executable(sudoku_win.exe WIN32 src/main.c)