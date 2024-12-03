#include <iostream>
#include <chrono>
#include <vector>
#include "Allocation.h"
#include "timer.cpp"

void benchmark_allocation(int number_of_allocations, std::size_t size, Memory_Linked_List::mmap_mode mode)
{
    mll.m_mmap_mode = mode;
    std::vector<intptr_t *> pointers;
    { // Allocation Time
        Timer timer;

        for (int i = 0; i < number_of_allocations; i++)
        {
            pointers.push_back(new intptr_t[size]);
        }

        std::cout << "Allocation time for " << number_of_allocations << " blocks of size " << size << std::endl;
    }

    { // Deallocation Time
        Timer timer;

        for (intptr_t *ptr : pointers)
        {
            delete[] ptr;
        }

        std::cout << "Deallocation time for " << number_of_allocations << " blocks of size " << size << std::endl;
    }
}

void benchmark_std_allocator(int number_of_allocations, std::size_t size)
{

    std::vector<intptr_t *> pointers;

    { // Allocation Time
        Timer timer;
        std::allocator<intptr_t> alloc;
        for (int i = 0; i < number_of_allocations; i++)
        {
            intptr_t *ptr = alloc.allocate(size);

            for (std::size_t j = 0; j < size; ++j)
            {
                ptr[j] = 0;
            }
        }

        std::cout << std::endl;
        std::cout << "std::allocator Allocation time for " << number_of_allocations << " blocks of size " << size << std::endl;
    }

    { // Deallocation Time
        Timer timer;
        std::allocator<intptr_t> alloc;
        for (intptr_t *ptr : pointers)
        {
            alloc.deallocate(ptr, size);
        }
        std::cout << "std::allocator Deallocation time for " << number_of_allocations << " blocks of size " << size << std::endl;
    }
}

void runBenchmarks()
{
    std::cout << "Benchmarking with sbrk:" << std::endl;
    std::cout << std::endl;
    benchmark_allocation(1000, 1, Memory_Linked_List::mmap_mode::sbrk);
    std::cout << std::endl;
    std::cout << "Benchmarking with mmap:" << std::endl;
    std::cout << std::endl;
    benchmark_allocation(1000, 1, Memory_Linked_List::mmap_mode::mmap);
    std::cout << std::endl;
    std::cout << "Benchmarking with std::allocator:" << std::endl;
    std::cout << std::endl;
    benchmark_std_allocator(1000, 1);
    std::cout << std::endl;
}
