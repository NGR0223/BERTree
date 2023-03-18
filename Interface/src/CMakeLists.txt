CMAKE_MINIMUM_REQUIRED(VERSION 3.20)


#include_directories(../../Base/include)
#include_directories(../../IndefiniteArray/include)
#include_directories(../../MBTree/include)
#
#aux_source_directory(../../Base/src Base)
#aux_source_directory(../../IndefiniteArray/src IndefiniteArray)
#aux_source_directory(../../IndefiniteArray/src MBTree)

aux_source_directory(. DIR_SRC)

add_library(BERTreeInterface SHARED ${DIR_SRC})

target_link_libraries(BERTreeInterface Base)
target_link_libraries(BERTreeInterface IndefiniteArray)
target_link_libraries(BERTreeInterface MBTree)