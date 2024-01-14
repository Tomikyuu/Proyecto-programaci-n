cmake_minimum_required(VERSION 3.3)
project(FundamentosProgramacionBueno C)

set(CMAKE_C_STANDARD 11)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)

include_directories(${GTK3_INCLUDE_DIRS})
link_directories(${GTK3_LIBRARY_DIRS})
add_definitions(${GTK3_CFLAGS_OTHER})

set(SOURCE_FILES main.c
        userInfoManager.c
        fileManager.c)

add_executable(FundamentosProgramacionBueno ${SOURCE_FILES})

target_link_libraries(FundamentosProgramacionBueno ${GTK3_LIBRARIES})

