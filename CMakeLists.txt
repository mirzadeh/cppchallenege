cmake_minimum_required(VERSION 3.0)

project(cppchallenge)
include_directories("include")
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++11")

add_executable(${PROJECT_NAME} "main.cpp")
