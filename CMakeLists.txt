cmake_minimum_required(VERSION 3.16)
project(SudokuSolver)

find_package(Boost REQUIRED COMPONENTS filesystem)

set(CMAKE_CXX_STANDARD 17)

add_executable(SudokuSolver main.cpp src/Sudoku.cpp src/Sudoku.h)

target_link_libraries(SudokuSolver Boost::filesystem)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/assignments DESTINATION ${CMAKE_BINARY_DIR})