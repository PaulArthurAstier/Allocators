#include <iostream>
#include <cassert>
#include "allocator.h"


int main()
{

    auto mll = Memory_Linked_List();
    char* letter1 = (char*)mll.alloc(sizeof(char));
    *letter1 = 'a';
    auto letter2 = (double*)mll.alloc(sizeof(double));
    *letter2 = 2;
    char* letter3 = (char*)mll.alloc(sizeof(char));
    *letter3 = 'c';
    char* letter4 = (char*)mll.alloc(sizeof(char));
    *letter4 = 'd';

    mll.free(reinterpret_cast<intptr_t *>(letter2));

    char* letter5 = (char*)mll.alloc(sizeof(char));
    *letter5 = 'p';

    mll.print_all_memory();

    std::cout << *letter1 << std::endl;
    std::cout << *letter2 << std::endl;
    std::cout << *letter3 << std::endl;
    std::cout << *letter4 << std::endl;
    std::cout << *letter5 << std::endl;
}
