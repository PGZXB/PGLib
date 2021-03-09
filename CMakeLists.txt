set(DCMAKE_SH="CMAKE_SH-NOTFOUND")

cmake_minimum_required(VERSION 3.16)

add_definitions(-Wall)

set(CMAKE_CXX_STANDARD 20)

include_directories(include)

file(GLOB src_files src/*.cpp)

project(PGLibTest)
add_executable(PGLibTest  ${src_files})
