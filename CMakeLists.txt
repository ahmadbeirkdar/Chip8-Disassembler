cmake_minimum_required(VERSION 3.16)
project(Chip8_Disassembler)

set(CMAKE_CXX_STANDARD 20)

add_executable(Chip8_Disassembler main.cpp Chip8.cpp Chip8.hpp)