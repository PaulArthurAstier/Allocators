#include <iostream>
#include "Allocation.h"
#include "benchmark.cpp"

int main()
{

    char *word0 = new char;
    *word0 = 'a';
    char *word1 = new char;
    *word1 = 'b';
    char *word2 = new char;
    *word2 = 'c';
    char *word3 = new char;
    *word3 = 'd';
    char *word4 = new char;
    *word4 = 'e';
    char *word5 = new char;
    *word5 = 'f';

    mll.print_all_memory();
    std::cout << "<<<<<<<<freelist>>>>>>>>" << std::endl;
    mll.print_all_free_memory();

    runBenchmarks();

    delete word0;
    delete word1;
    delete word2;
    delete word3;
    delete word4;
    delete word5;

    runBenchmarks();

    return 0;
}
