cmake_minimum_required(VERSION 3.23)
project(Labo_1_PRG2_J_2023 C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "-Wall -Wextra -Wconversion -Wsign-conversion -pedantic")

include_directories(.)

add_executable(Labo_1_PRG2_J_2023
        listes_dynamiques.h listes_dynamiques.c main.c )
