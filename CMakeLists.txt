cmake_minimum_required(VERSION 3.0)

project(cppchallenge)
enable_testing()

include_directories("include")
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++11")

add_executable(square.test "test/square.cpp")
add_executable(rectangle.test "test/rectangle.cpp")

add_test(NAME small COMMAND square.test "${CMAKE_SOURCE_DIR}/data/small.txt")
add_test(NAME square COMMAND square.test "${CMAKE_SOURCE_DIR}/data/square.txt")
add_test(NAME rectangle COMMAND rectangle.test "${CMAKE_SOURCE_DIR}/data/rectangle.txt")
