cmake_minimum_required(VERSION 3.27)
project(ProyectoFundamentos C)

set(CMAKE_C_STANDARD 11)

add_executable(ProyectoFundamentos main.c
        fileManager.c
        userInfoManager.c)
