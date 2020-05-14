include_directories(${CMAKE_SOURCE_DIR}/lib)

# Sourcecode file(s) that are part of the Program
set(SOURCES
    main.c
)

add_executable(sudoku ${SOURCES})
add_executable(sudoku_win.exe WIN32 ${SOURCES})