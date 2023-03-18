cmake_minimum_required(VERSION 3.20)

aux_source_directory(. DIR_SRC)

ADD_LIBRARY(MBTree SHARED ${DIR_SRC})