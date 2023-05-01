//
// Created by Paul-Arthur on 19/04/2023.
//

#ifndef ALLOCATORSANDMEMORYPOOL_ALLOCATION_H
#define ALLOCATORSANDMEMORYPOOL_ALLOCATION_H

#include "allocator.h"

// holds all the memory
inline static Memory_Linked_List mll{};

// overriding the new operator
void *operator new(std::size_t size)
{
    auto pointer = mll.alloc(size);
    return pointer;
}

// overriding the delete operator
void operator delete(void *pointer) _GLIBCXX_USE_NOEXCEPT
{
    mll.free(static_cast<intptr_t *>(pointer));
}

#endif //ALLOCATORSANDMEMORYPOOL_ALLOCATION_H
