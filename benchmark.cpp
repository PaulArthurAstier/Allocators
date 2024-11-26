#include <iostream>
#include <chrono>
#include <vector>
#include <random>
#include <numeric>
#include <algorithm>
#include "Allocation.h" // Include your allocator header

// Structure to hold benchmark configurations
struct BenchmarkConfig
{
    int num_allocations;
    std::size_t size;
    std::string allocation_pattern; // e.g., "sequential", "random"
    Memory_Linked_List::search_mode search_mode;
};

// Function to perform allocations based on the specified pattern
std::vector<intptr_t *> allocate(const BenchmarkConfig &config)
{
    std::vector<intptr_t *> pointers;
    pointers.reserve(config.num_allocations);

    std::size_t totalSize = config.size * sizeof(intptr_t); // Calculate total size in bytes

    if (config.allocation_pattern == "sequential")
    {
        for (int i = 0; i < config.num_allocations; ++i)
        {
            pointers.push_back(reinterpret_cast<intptr_t *>(mll.alloc(totalSize))); // Allocate with total size
        }
    }
    else if (config.allocation_pattern == "random")
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dist(0, config.num_allocations - 1); // Use to shuffle

        // Allocate all memory up front
        std::vector<intptr_t *> allocated_memory;
        allocated_memory.reserve(config.num_allocations);
        for (int i = 0; i < config.num_allocations; i++)
        {
            allocated_memory.push_back(reinterpret_cast<intptr_t *>(mll.alloc(totalSize))); // Allocate with total size
        }

        std::shuffle(allocated_memory.begin(), allocated_memory.end(), gen);
        pointers = allocated_memory; // Assign shuffled pointers
    }
    else
    {
        throw std::runtime_error("Unknown allocation pattern: " + config.allocation_pattern);
    }

    return pointers;
}

// Function to deallocate memory
void deallocate(std::vector<intptr_t *> &pointers)
{
    for (intptr_t *ptr : pointers)
    {
        mll.free(ptr); // Directly free using mll
    }
    pointers.clear(); // Clear the vector after deallocation
}

// Function to run a single benchmark and return the duration
long long run_benchmark(const BenchmarkConfig &config)
{
    mll.m_search_mode = config.search_mode; // Set search mode

    auto start = std::chrono::high_resolution_clock::now();
    auto pointers = allocate(config); // Use allocation pattern
    deallocate(pointers);

    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
}

void runBenchmarks()
{
    std::cout << "Starting Benchmarks..." << std::endl;

    const int num_runs = 5; // Number of benchmark runs
    std::vector<BenchmarkConfig> configs = {
        {10000, 1, "sequential", Memory_Linked_List::search_mode::first_fit},
        {10000, 1, "sequential", Memory_Linked_List::search_mode::next_fit},
        {10000, 1, "sequential", Memory_Linked_List::search_mode::best_fit},
        {10000, 1, "sequential", Memory_Linked_List::search_mode::free_list},
        {1000, 1024, "sequential", Memory_Linked_List::search_mode::first_fit},
        {100, 1024 * 1024, "sequential", Memory_Linked_List::search_mode::first_fit},

        // Random Allocation Pattern tests
        {10000, 1, "random", Memory_Linked_List::search_mode::first_fit},
        {10000, 1, "random", Memory_Linked_List::search_mode::next_fit},
        {10000, 1, "random", Memory_Linked_List::search_mode::best_fit},
        {10000, 1, "random", Memory_Linked_List::search_mode::free_list},

    };

    for (const auto &config : configs)
    {
        std::vector<long long> durations;
        for (int i = 0; i < num_runs; ++i)
        {
            durations.push_back(run_benchmark(config));
        }

        // Calculate statistics (average)
        double average_duration = std::accumulate(durations.begin(), durations.end(), 0.0) / num_runs;

        std::cout << "Benchmark: " << config.num_allocations << " blocks of size " << config.size
                  << ", pattern: " << config.allocation_pattern
                  << ", search_mode: " << static_cast<int>(config.search_mode) // Show as integer
                  << " - Average duration: " << average_duration << " microseconds" << std::endl;
    }

    std::cout << "Benchmarks Complete." << std::endl;
}
