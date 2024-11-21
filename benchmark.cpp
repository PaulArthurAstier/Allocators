#include <iostream>
#include <chrono>
#include <vector>
#include "Allocation.h" // Include your allocator header

void benchmark_allocation(int num_allocations, std::size_t size)
{
    auto start = std::chrono::high_resolution_clock::now();
    std::vector<intptr_t *> pointers;
    for (int i = 0; i < num_allocations; ++i)
    {
        pointers.push_back(new intptr_t[size]); // Allocate
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    std::cout << "Allocation of " << num_allocations << " blocks of size " << size
              << ": " << duration.count() << " microseconds" << std::endl;

    start = std::chrono::high_resolution_clock::now();
    for (intptr_t *ptr : pointers)
    {
        delete[] ptr; // Deallocate
    }
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    std::cout << "Deallocation of " << num_allocations << " blocks of size " << size
              << ": " << duration.count() << " microseconds" << std::endl;
    // ... (Benchmarking code from previous responses) ...
}

void runBenchmarks()
{
    std::cout << "Starting Benchmarks..." << std::endl;

    benchmark_allocation(10000, 1);         // Small allocations
    benchmark_allocation(1000, 1024);       // Medium allocations
    benchmark_allocation(100, 1024 * 1024); // Large allocations

    // Benchmark different search strategies if your allocator supports them. It seems like yours do.
    mll.m_search_mode = Memory_Linked_List::search_mode::first_fit;
    benchmark_allocation(10000, 1);

    mll.m_search_mode = Memory_Linked_List::search_mode::next_fit;
    benchmark_allocation(10000, 1);

    mll.m_search_mode = Memory_Linked_List::search_mode::best_fit;
    benchmark_allocation(10000, 1);

    mll.m_search_mode = Memory_Linked_List::search_mode::free_list;
    benchmark_allocation(10000, 1);

    std::cout << "Benchmarks Complete." << std::endl;
}
