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
    using pointer = T*;
    using const_pointer = const T*;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;

    allocator_wrapper() noexcept = default;
    ~allocator_wrapper() noexcept = default;

    template <typename U>
    allocator_wrapper(const allocator_wrapper<U>&) noexcept {}

    T* allocate(std::size_t size) noexcept
    {
        intptr_t* ptr = mll.alloc(size * sizeof(T));
        return reinterpret_cast<T*>(ptr);
    }

    void deallocate(T* data, std::size_t) noexcept
    {
        mll.free(reinterpret_cast<intptr_t*>(data));
    }

    bool operator==(const allocator_wrapper&) const noexcept { return true; }
    bool operator!=(const allocator_wrapper&) const noexcept { return false; }

    template <typename U>
    struct rebind
    {
        using other = allocator_wrapper<U>;
    };

private:

    Memory_Linked_List mll{};
};

#endif //ALLOCATOR_WRAPPER_H
