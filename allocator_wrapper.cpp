#include "allocator_wrapper.h"
#include "allocator.h"

template <typename T>
T* allocator_wrapper<T>::allocate(std::size_t n) noexcept
{
    return mll.alloc(n);
}

template <typename T>
void allocator_wrapper<T>::deallocate(T* p, std::size_t) noexcept
{
    mll.free(p);
}
