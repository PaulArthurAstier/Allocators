#include <iostream>
#include <cassert>
#include "allocator.h"

int main()
{

    auto mll = Memory_Linked_List();
    char* letter1 = (char*)mll.alloc(5 * sizeof(char));
    letter1[0] = '1';
    letter1[1] = 'b';
    letter1[2] = 'c';
    letter1[3] = 'd';
    letter1[4] = '3';


    auto letter2 = (char *)mll.alloc(sizeof(char));
    *letter2 = '2';

    char* letter3 = (char*)mll.alloc(sizeof(char));
    *letter3 = '3';

    char* letter4 = (char*)mll.alloc(sizeof(char));
    *letter4 = '4';

    auto letter5 = (char *)mll.alloc(sizeof(char));
    *letter5 = '5';

    char* letter6 = (char*)mll.alloc(sizeof(char));
    *letter6 = '6';

    char* letter7 = (char*)mll.alloc(sizeof(char));
    *letter7 = '7';

    char* letter8 = (char*)mll.alloc(sizeof(char));
    *letter8 = '8';

    mll.free(reinterpret_cast<intptr_t *>(letter5));
    mll.free(reinterpret_cast<intptr_t *>(letter4));
    mll.free(reinterpret_cast<intptr_t *>(letter8));
    mll.free(reinterpret_cast<intptr_t *>(letter3));
    mll.free(reinterpret_cast<intptr_t *>(letter6));
    mll.free(reinterpret_cast<intptr_t *>(letter2));
    mll.free(reinterpret_cast<intptr_t *>(letter7));
    mll.free(reinterpret_cast<intptr_t *>(letter1));


    char* letter9 = (char*)mll.alloc(sizeof(char));
    *letter9 = 'f';

    char* letter10 = (char*)mll.alloc(sizeof(char));
    *letter10 = 'g';

    char* letter11 = (char*)mll.alloc(sizeof(char));
    *letter11 = 'h';

    char* letter12 = (char*)mll.alloc(sizeof(char));
    *letter12 = 'i';

    char* letter13 = (char*)mll.alloc(sizeof(char));
    *letter13 = 'j';

    char* letter14 = (char*)mll.alloc(sizeof(char));
    *letter14 = 'k';

    char* letter15 = (char*)mll.alloc(sizeof(char));
    *letter15 = 'l';

    char* letter16 = (char*)mll.alloc(sizeof(char));
    *letter16 = 'm';


    mll.print_all_memory();

    mll.print_counter();

    std::cout << letter1[0] << std::endl;
    std::cout << *letter2 << std::endl;
    std::cout << *letter3 << std::endl;
    std::cout << *letter4 << std::endl;
    std::cout << *letter5 << std::endl;
    std::cout << *letter6 << std::endl;
    std::cout << *letter7 << std::endl;
    std::cout << *letter8 << std::endl;
    std::cout << *letter9 << std::endl;
    std::cout << *letter10 << std::endl;
    std::cout << *letter11 << std::endl;
    std::cout << *letter12 << std::endl;
    std::cout << *letter13 << std::endl;
    std::cout << *letter14 << std::endl;
    std::cout << *letter15 << std::endl;
    std::cout << *letter16 << std::endl;





}
