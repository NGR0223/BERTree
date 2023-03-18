CMAKE_MINIMUM_REQUIRED(VERSION 3.20)

aux_source_directory(../../Base/src Base)
aux_source_directory(../../IndefiniteArray/src IndefiniteArray)
aux_source_directory(../../MBTree/src MBTree)

aux_source_directory(. DIR_SRC)

add_library(BERTreeDyLib SHARED ${Base} ${IndefiniteArray} ${MBTree} ${DIR_SRC})