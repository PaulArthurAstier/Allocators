#ifndef ALLOCATOR_WRAPPER_H
#define ALLOCATOR_WRAPPER_H

#include <cstddef>
#include <memory>
#include "allocator.h" 

template <typename T>
class allocator_wrapper
{    
public:
    using value_type = T;

    T* allocate(std::size_t n) noexcept;

    void deallocate(T* p, std::size_t) noexcept;

private:

    inline static Memory_Linked_List mll{};
};


#endif //ALLOCATOR_WRAPPER_H
