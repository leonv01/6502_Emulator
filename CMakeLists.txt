cmake_minimum_required(VERSION 3.26)
project(6502_Emulator)

set(CMAKE_CXX_STANDARD 11)

add_executable(6502_Emulator main.cpp
        System/CPU/CPU.cpp
        System/CPU/CPU.h
        System/CPU/Register.cpp
        System/CPU/Register.h
        System/Memory.cpp
        System/Memory.h)
