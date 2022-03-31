cmake_minimum_required(VERSION 3.19)
project(t.zip)

set(CMAKE_C_STANDARD 11)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++ -static-libgcc")

include_directories(.)

add_executable(t.zip
        hangman.c
        hangman.h
        functions.c
        functions.h
        main.c
        wordlist.txt
        )
