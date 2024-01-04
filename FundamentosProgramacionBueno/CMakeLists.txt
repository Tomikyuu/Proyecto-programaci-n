cmake_minimum_required(VERSION 3.27)
project(FundamentosProgramacionBueno C)

set(CMAKE_C_STANDARD 11)

add_executable(FundamentosProgramacionBueno main.c
        fileManager.c
        userInfoManager.c)
