cmake_minimum_required(VERSION 3.17.0)

project(Promyczek VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)


#MAIN PROJECT
add_subdirectory(lib/stb)
add_subdirectory(src)