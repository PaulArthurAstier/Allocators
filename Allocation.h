#ifndef ALLOCATORSANDMEMORYPOOL_ALLOCATION_H
#define ALLOCATORSANDMEMORYPOOL_ALLOCATION_H

#include "allocator.h"
#include "allocator_wrapper.h"

#include <memory>
#include <vector>
#include <map>
#include <list>
#include <set> 

/**
 * This file is just used to override standard containers and
 * allocators.
 */

inline static Memory_Linked_List mll{};
inline static allocator_wrapper<intptr_t> memory{};

void* operator new(std::size_t size)
{
    return memory.allocate(size);
}

void operator delete(void* pointer) noexcept
{
    memory.deallocate(static_cast<intptr_t*>(pointer), 0);
}

void* operator new[](std::size_t size)
{
    return memory.allocate(size);
}

void operator delete[](void* pointer) noexcept
{
    memory.deallocate(static_cast<intptr_t*>(pointer), 0);
}

template <typename T>
using vector = std::vector<T, allocator_wrapper<T>>;

template <typename K, typename V>
using map = std::map<K, V, std::less<K>, allocator_wrapper<std::pair<const K, V>>>;

template <typename T>
using list = std::list<T, allocator_wrapper<T>>;

template <typename T>
using set = std::set<T, std::less<T>, allocator_wrapper<T>>;

#endif // ALLOCATORSANDMEMORYPOOL_ALLOCATION_H
