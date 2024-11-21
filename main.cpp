#include <iostream>
#include "Allocation.h"
#include <vector>
#include "benchmark.cpp"
#include <memory>
// std::allocator

int main()
{

    char *word0 = new char;
    *word0 = 'a';
    int *num1 = new int[5];
    *num1 = 1;

    mll.print_all_memory();
    std::cout << "<<<<<<<<freelist>>>>>>>>" << std::endl;
    mll.print_all_free_memory();
<<<<<<< HEAD
=======

    runBenchmarks();

    return 0;
>>>>>>> 730dc91109a25867627a6adc7f66eb5b80cf07a8
}
