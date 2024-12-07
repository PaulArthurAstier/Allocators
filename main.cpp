#include <iostream>
#include "Allocation.h"
#include "benchmark.cpp"
#include <memory>
#include <vector>
#include <map>         
#include "allocator_wrapper.h"
// std::allocator

int main()
{

  // Ensure memory pool is initialized by instantiating a CustomAllocator object
    CustomAllocator<int> allocator;
    
    // Access the memory pool using the getter function
    Memory_Linked_List* memoryPool = CustomAllocator<int>::memory_pool;

    // Test 1: Allocation and Deallocation with `std::vector<int>`
    std::cout << "Test 1: Allocating and Printing Integers with CustomAllocator\n";
    std::vector<int, CustomAllocator<int>> myVector;
    myVector.push_back(11);
    myVector.push_back(20);

    // Print the memory state assuming data type is `int`
    std::cout << "\nMemory State after pushing integers into vector:\n";
    memoryPool->print_all_memory_as_int();

    myVector.push_back(30);
    myVector.push_back(11);
    myVector.push_back(20);
    myVector.push_back(30);
    myVector.push_back(11);
    myVector.push_back(20);
    myVector.push_back(30);
    myVector.push_back(11);
    myVector.push_back(20);
    myVector.push_back(30);


    // Print the memory state assuming data type is `int`
    std::cout << "\nMemory State after pushing integers into vector:\n";
    memoryPool->print_all_memory_as_int();

    myVector.clear();  // This will trigger deallocation for all elements

    // Print the memory state after deallocation
    std::cout << "\nMemory State after clearing vector of integers:\n";
    memoryPool->print_all_memory_as_int();


    // // Test 2: Allocation and Deallocation with `std::vector<char>`
    // std::cout << "\nTest 2: Allocating and Printing Characters with CustomAllocator\n";
    // std::vector<char, CustomAllocator<char>> charVector;
    // charVector.push_back('A');
    // charVector.push_back('B');
    // charVector.push_back('C');

    // // Print the memory state assuming data type is `char`
    // std::cout << "\nMemory State after pushing characters into vector:\n";
    // memoryPool->print_all_memory_as_char();

    // charVector.clear();  // This will trigger deallocation for all elements

    // // Print the memory state after deallocation
    // std::cout << "\nMemory State after clearing vector of characters:\n";
    // memoryPool->print_all_memory_as_char();

    
    // // Test 3: Reallocation in Vector (Push beyond initial capacity)
    // std::cout << "\nTest 3: Reallocation Test with std::vector<int>\n";
    // std::vector<int, CustomAllocator<int>> reallocateTestVector;
    // for (int i = 0; i < 50; ++i) {
    //     reallocateTestVector.push_back(i);  // This will force the vector to reallocate memory multiple times
    // }

    // // Print the memory state after reallocations (int case)
    // std::cout << "\nMemory State after reallocation in vector (integers):\n";
    // memoryPool->print_all_memory_as_int();

    // reallocateTestVector.clear();  // Clear the vector and deallocate memory

    // // Print the memory state after clearing the reallocated vector
    // std::cout << "\nMemory State after clearing reallocated vector (integers):\n";
    // memoryPool->print_all_memory_as_int();

    
    return 0;

    // char *word0 = new char;
    // *word0 = 'a';

    // int *num1 = new int[5];
    // *num1 = 1;

    // mll.print_all_memory();
    // std::cout << "<<<<<<<<freelist>>>>>>>>" << std::endl;
    // mll.print_all_free_memory();

    // return 0;
}
