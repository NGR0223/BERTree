cmake_minimum_required(VERSION 3.22)
project(BERTree C)

set(CMAKE_C_STANDARD 17)

add_subdirectory(Interface/src)

add_executable(BERTree main.c)

target_link_libraries(BERTree BERTreeInterface)

