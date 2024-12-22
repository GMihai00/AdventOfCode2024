cmake_minimum_required(VERSION 3.28)

set(CMAKE_CXX_STANDARD 17) 

project(day11)

add_executable(${PROJECT_NAME} ./src/main.cpp ./src/models/StoneLine.cpp)