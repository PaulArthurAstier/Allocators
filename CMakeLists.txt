cmake_minimum_required(VERSION 3.21)
project(Allocators)

set(CMAKE_CXX_STANDARD 20)

add_executable(allocator main.cpp allocator.cpp allocator.h Allocation.h allocator_wrapper.h)
