cmake_minimum_required(VERSION 3.22)
project(test C)

set(CMAKE_C_STANDARD 17)

add_executable(test ../Base/src/base.c ../IndefiniteArray/src/indefiniteArray.c ../MBTree/src/tree.c test.c)

