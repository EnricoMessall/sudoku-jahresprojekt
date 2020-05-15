cmake_minimum_required(VERSION 3.16)
project(jahresprojekt C)

set(CMAKE_C_STANDARD 99)
# include_directories(src) ##not needed

add_executable(sudoku src/main.c)
# add_executable(sudoku_win.exe WIN32 src/main.c) ## TODO: Linking not working for Exe file

# https://discourse.cmake.org/t/cannot-get-tiny-test-with-an-extrenal-static-library-to-run/467
list(APPEND CMAKE_PREFIX_PATH ${CMAKE_SOURCE_DIR}/lib)
find_package(SQLite3)
if(SQLite3_FOUND)
    target_link_libraries(sudoku PRIVATE SQLite::SQLite3)
endif(SQLite3_FOUND)