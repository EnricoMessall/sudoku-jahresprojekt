cmake_minimum_required(VERSION 3.16)
project(jahresprojekt C)

set(CMAKE_C_STANDARD 99)
include_directories(src)
include_directories(${CMAKE_SOURCE_DIR}/src/leaderboard)
include_directories(${CMAKE_SOURCE_DIR}/src/GUI)
include_directories(${CMAKE_SOURCE_DIR}/src/Generator)

add_executable(sudoku src/main.c)
# add_executable(sudoku_win.exe WIN32 src/main.c) ## TODO: Check if this is working on Windows

# Src: https://dmerej.info/blog/post/chuck-norris-part-2-sqlite-conan/
add_library(sqlite3 STATIC IMPORTED)
set_target_properties(sqlite3
  PROPERTIES
  IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/lib/libsqlite3.a
  INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_SOURCE_DIR}/lib
)

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
  set_target_properties(sqlite3
    PROPERTIES
      INTERFACE_LINK_LIBRARIES "dl;pthread"
   )
endif()

target_link_libraries(sudoku sqlite3)