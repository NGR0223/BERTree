cmake_minimum_required(VERSION 3.20)

include_directories(../../IndefiniteArray/include)

aux_source_directory(../../IndefiniteArray/src IndefiniteArray)

aux_source_directory(. DIR_SRC)

ADD_LIBRARY(MBTree SHARED ${IndefiniteArray} ${DIR_SRC})