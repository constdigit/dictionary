cmake_minimum_required(VERSION 3.5)
project(dictionary_EProject)

set(CMAKE_C_STANDARD 99)
#set(CMAKE_BUILD_TYPE Debug)
set(HEADERS ../headers/Record.h ../headers/Entry.h ../headers/HashMap.h ../headers/FileWork.h)
set(SOURCES ../main.c ../sources/Record.c ../sources/Entry.c ../sources/HashMap.c ../sources/FileWork.c)

add_executable(dictionary_EProject ${SOURCES} ${HEADERS})
