cmake_minimum_required(VERSION 3.21)
project(AllocatorsAndMemoryPool)

set(CMAKE_CXX_STANDARD 20)

add_executable(AllocatorsAndMemoryPool main.cpp allocator.cpp allocator.h Allocation.h)
