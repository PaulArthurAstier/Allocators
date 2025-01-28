#include <iostream>
#include "benchmark.cpp"
#include "Allocation.h"

// std::allocator

int main()
{
    int* scalar = new int(42);
    std::cout << "Scalar: " << *scalar << std::endl;
    delete scalar;

    int* array = new int[5]{1, 2, 3, 4, 5};
    std::cout << "Array: ";
    for (int i = 0; i < 5; ++i)
    {
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;
    delete[] array;

    vector<int> vec = {1, 2, 3, 4, 5};
    vec.push_back(6);

    std::cout << "Vector contents: ";
    for (const auto& val : vec)
    {
        std::cout << val << " ";
    }
    std::cout << std::endl;

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

    list<float> my_list = {1.1, 2.2, 3.3};
    my_list.push_back(4.4);

    std::cout << "List contents: ";
    for (const auto& val : my_list)
    {
        std::cout << val << " ";
    }
    std::cout << std::endl;

    vector<std::basic_string<char, std::char_traits<char>, allocator_wrapper<char>>> vecv{
        "Hello very long string that won't feet into 32 bytes of the buffer that's in the string",
        "Hello very long string that won't feet into 32 bytes of the buffer that's in the string",
        "Hello very long string that won't feet into 32 bytes of the buffer that's in the string",
        "Hello very long string that won't feet into 32 bytes of the buffer that's in the string",
        "Hello very long string that won't feet into 32 bytes of the buffer that's in the string"

    };

    for (auto&& s: vecv)
        std::cout << s << '\n';


    runBenchmarks();
    
    return 0;
}
