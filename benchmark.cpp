#include <iostream>
#include <chrono>
#include <vector>
#include <array>
#include "Allocation.h"
#include "timer.cpp"

void benchmark_allocation(int number_of_allocations, std::size_t size, Memory_Linked_List::mmap_mode mode, Memory_Linked_List::search_mode search = Memory_Linked_List::search_mode::first_fit)
{
    mll.m_mmap_mode = mode;           // Sets the memory allocation method for the custom allocator.
    mll.set_search_mode(search);      // Sets the search mode for the custom allocator.
    std::vector<intptr_t *> pointers; // Creates a vector to store pointers to the allocated memory blocks.

    {                // Allocation Time
        Timer timer; // An instance of the Timer class is created to measure the allocation time.

        for (int i = 0; i < number_of_allocations; i++) // Loop allocates blocks of memory, each of size elements, using the custom allocator.
        {
            pointers.push_back(new intptr_t[size]); // Allocates a new block of memory by adding the address of the newly allocated memory block to the pointers vector.
        }

        std::cout << "Allocation time for " << number_of_allocations << " blocks of size " << size
                  << " utilising " << (mode == Memory_Linked_List::mmap_mode::sbrk ? "sbrk" : "mmap")
                  << " and " << (search == Memory_Linked_List::search_mode::first_fit ? "first_fit" : (search == Memory_Linked_List::search_mode::next_fit ? "next_fit" : (search == Memory_Linked_List::search_mode::best_fit ? "best_fit" : "free_list"))) << std::endl;
    }

    { // Deallocation Time
        Timer timer;

        for (intptr_t *ptr : pointers)
        {
            delete[] ptr;
        }
        std::cout << std::endl;
        std::cout << "Deallocation time for " << number_of_allocations << " blocks of size " << size
                  << " utilising " << (mode == Memory_Linked_List::mmap_mode::sbrk ? "sbrk" : "mmap")
                  << " and " << (search == Memory_Linked_List::search_mode::first_fit ? "first_fit" : (search == Memory_Linked_List::search_mode::next_fit ? "nex_fit" : (search == Memory_Linked_List::search_mode::best_fit ? "best_fit" : "free_list"))) << std::endl;
        std::cout << std::endl;
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
            pointers.push_back(ptr); // storing the pointer to each allocated block of memory
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
        std::cout << std::endl;
        std::cout << "std::allocator Deallocation time for " << number_of_allocations << " blocks of size " << size << std::endl;
    }
}

void runBenchmarks()
{

    /*
     * A fixed size C std array to hold the memory map modes
     * A fixed size C std array to hold the search modes.
     * A vector holding the differnent allocation sizes.
     */
    std::array<Memory_Linked_List::mmap_mode, 2> modes = {Memory_Linked_List::mmap_mode::sbrk, Memory_Linked_List::mmap_mode::mmap};
    std::array<Memory_Linked_List::search_mode, 4> search_modes = {Memory_Linked_List::search_mode::first_fit, Memory_Linked_List::search_mode::next_fit, Memory_Linked_List::search_mode::best_fit, Memory_Linked_List::search_mode::free_list};
    std::vector<std::size_t> allocationSizes = {1, 10, 100, 1000};

    /*
     * Nested for loops to iterate through all the possible mode combinations.
     * Most Outer loop iterates through the memory map modes.
     * Inner middle loop iterates through the search modes.
     * Inner loop iterates through the different sizes of allocation.
     * The funtion call defines the the no. of allocations, size of each allocation and modal combination.
     */
    for (auto mode : modes)
    {
        for (auto search : search_modes)
        {
            for (std::size_t size : allocationSizes)
            {

                std::cout << "Benchmarking with" << (mode == Memory_Linked_List::mmap_mode::sbrk ? " sbrk" : " mmap")
                          << " and " << (search == Memory_Linked_List::search_mode::first_fit ? "first_fit" : (search == Memory_Linked_List::search_mode::next_fit ? "next_fit" : (search == Memory_Linked_List::search_mode::best_fit ? "best_fit" : "free_list")))
                          << ":" << std::endl;

                benchmark_allocation(100, size, mode, search);
                std::cout
                    << std::endl;
            }
        }

        // The function below benchmarks the std::allocator with the same set of allocation sizes.
        std::cout << "Benchmarking with std::allocator:" << std::endl;
        for (std::size_t size : allocationSizes)

        {
            benchmark_std_allocator(1000, size);
            std::cout << std::endl;
        }
    };
}