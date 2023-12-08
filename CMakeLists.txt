cmake_minimum_required(VERSION 3.5)

project(UniSingleton)
message(STATUS "BINARY dir:" ${PROJECT_BINARY_DIR})
message(STATUS "SOURCE dir:" ${PROJECT_SOURCE_DIR})

# add the binary tree to the search path for include files
include_directories("${PROJECT_SOURCE_DIR}")

set(SOURCES UniSingleton.cpp  main.cpp)

# add the executable
add_executable(UniSingleton ${SOURCES})