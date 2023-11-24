cmake_minimum_required(VERSION 3.26)
project(optimisation_d_une_ligne_d_assemblage_ing2_tg_2023_2024_2_0 C)

set(CMAKE_C_STANDARD 99)

include_directories(.)

add_executable(optimisation_d_une_ligne_d_assemblage_ing2_tg_2023_2024_2_0
        header.h
        main.c
        sous_programmes_Max.c
        sousprogrammeGabriel.c
        sousprogrammeJulien.c
)
