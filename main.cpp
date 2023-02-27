#include <iostream>
#include <cassert>
#include "allocator.h"




int main()
{

    auto mll = Memory_Linked_List();
    int* num = (int*)mll.alloc(sizeof(int));
    *num = 2;

    if (num == nullptr)
    {
        std::cout << "Null pointer has been returned";
    }

    else
    {
        std::cout << "Memory has been allocated at address " << *num << std::endl;
    }


}
