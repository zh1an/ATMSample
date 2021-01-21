cmake_minimum_required(VERSION 3.0)
project(ATMSample)

set(CMAKE_CXX_STANDARD 11)

#aux_source_directory(
#        source/misc
#        source/core
#        SRC_FILES)
include_directories(source)

add_executable(ATMSample main.cpp ${SRC_FILES})