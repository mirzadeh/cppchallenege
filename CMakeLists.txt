cmake_minimum_required(VERSION 3.0)

project(cpp)
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++17")

add_executable(${PROJECT_NAME} "main.cpp")
