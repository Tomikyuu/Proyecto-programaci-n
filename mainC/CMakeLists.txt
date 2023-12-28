cmake_minimum_required(VERSION 3.27)
project(mainC C)

set(CMAKE_C_STANDARD 11)

add_executable(mainC main.c
        userInfoManager.c
        fileManager.c
        userInfoManager.h
        fileManager.h)
