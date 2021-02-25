cmake_minimum_required(VERSION 3.17)
project(lock_based_list)

set(CMAKE_CXX_STANDARD 17)

add_executable(lock_based_list src/main.cpp src/lock_based_list.cpp)