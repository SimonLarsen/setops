project(setops)
cmake_minimum_required(VERSION 2.6)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(include)

add_executable(test_exe
	src/test/test.cpp
)
