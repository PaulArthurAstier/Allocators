#include <iostream>
#include "benchmark.cpp"
#include "allocator_wrapper.h"

#include <memory>
#include <vector>
#include <map>   

// std::allocator

int main()
{
    std::vector<int, allocator_wrapper<int>> vec;

    // Add elements to the vector
    vec.push_back(10);
    vec.push_back(20);
    vec.push_back(30);

    // Print the elements
    for (const auto& val : vec)
    {
        std::cout << val << std::endl;
    }

    return 0;

    
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
