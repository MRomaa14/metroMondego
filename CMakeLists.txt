cmake_minimum_required(VERSION 3.26)
project(metroMondego C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(metroMondego
        ficheiros.c
        ficheiros.h
        linha.c
        linha.h
        main.c
        menus.c
        menus.h
        paragem.c
        paragem.h
        percurso.c
        percurso.h
        utils.c
        utils.h)
