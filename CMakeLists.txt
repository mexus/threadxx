cmake_minimum_required (VERSION 2.6)
project(threadxx)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Werror -Wall -Wextra -pthread")

add_subdirectory(test)

