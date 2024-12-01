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

    char *word1 = new char;
    *word1 = 'a';

    int *num2 = new int[5];
    *num2 = 1;

    char *word3 = new char;
    *word3 = 'a';

    int *num3 = new int[5];
    *num3 = 1;

    char *word4 = new char;
    *word4 = 'a';

    int *num5 = new int[5];
    *num5 = 1;


    mll.print_all_memory();
    std::cout << "<<<<<<<<freelist>>>>>>>>" << std::endl;
    mll.print_all_free_memory();

    runBenchmarks();

    return 0;
}
