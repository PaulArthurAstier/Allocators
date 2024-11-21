#include <iostream>
#include "Allocation.h"


int main()
{

    char *word0 = new char;
    *word0 = 'a';
    int *num1 = new int[5];
    *num1 = 1;

    mll.print_all_memory();
    std::cout << "<<<<<<<<freelist>>>>>>>>" << std::endl;
    mll.print_all_free_memory();


}
