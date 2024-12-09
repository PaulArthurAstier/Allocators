#include <iostream>
#include "benchmark.cpp"
#include "Allocation.h"

// std::allocator

int main()
{
    // Using aliased vector
    vector<int> vec = {1, 2, 3, 4, 5};
    vec.push_back(6);

    std::cout << "Vector contents: ";
    for (const auto& val : vec)
    {
        std::cout << val << " ";
    }
    std::cout << std::endl;

    // Using aliased map
    map<int, std::string> my_map;
    my_map[1] = "one";
    my_map[2] = "two";
    my_map[3] = "three";

    std::cout << "Map contents: ";
    for (const auto& [key, value] : my_map)
    {
        std::cout << "{" << key << ", " << value << "} ";
    }
    std::cout << std::endl;

    // Using aliased list
    list<float> my_list = {1.1, 2.2, 3.3};
    my_list.push_back(4.4);

    std::cout << "List contents: ";
    for (const auto& val : my_list)
    {
        std::cout << val << " ";
    }
    std::cout << std::endl;

    return 0;
}
