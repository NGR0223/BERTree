CMAKE_MINIMUM_REQUIRED(VERSION 3.20)

aux_source_directory(. DIR_SRC)

add_library(Base SHARED ${DIR_SRC})