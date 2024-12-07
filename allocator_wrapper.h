#ifndef CUSTOM_ALLOCATOR_WRAPPER_H
#define CUSTOM_ALLOCATOR_WRAPPER_H

#include <cstddef>
#include <memory>
#include "allocator.h" // Assuming this is the header where `Memory_Linked_List` is defined

template <typename T>
class CustomAllocator {
public:
    using value_type = T;

    CustomAllocator() noexcept {
        // Lazy initialization of the memory pool when the allocator is used
        if (memory_pool == nullptr) {
            memory_pool = new Memory_Linked_List();
        }
    }

    template <typename U>
    CustomAllocator(const CustomAllocator<U>&) noexcept {}

    ~CustomAllocator() = default;

    // Allocate memory using the Memory_Linked_List instance
    T* allocate(std::size_t n) {
        if (n > std::size_t(-1) / sizeof(T)) {
            throw std::bad_array_new_length();
        }
        intptr_t* ptr = memory_pool->alloc(n * sizeof(T));
        return reinterpret_cast<T*>(ptr);
    }

    // Deallocate memory using the Memory_Linked_List instance
    void deallocate(T* p, std::size_t) noexcept {
        memory_pool->free(reinterpret_cast<intptr_t*>(p));
    }

    template <typename U>
    struct rebind {
        using other = CustomAllocator<U>;
    };

    template <typename U>
    bool operator==(const CustomAllocator<U>&) const noexcept {
        return true; // Allocators are considered equal if they use the same memory pool
    }

    template <typename U>
    bool operator!=(const CustomAllocator<U>&) const noexcept {
        return false; // Allocators are considered equal if they use the same memory pool
    }

    static Memory_Linked_List* memory_pool; // Single pool for all instances

private:
    //static Memory_Linked_List* memory_pool; // Single pool for all instances
};

// Define the static memory pool
template <typename T>
Memory_Linked_List* CustomAllocator<T>::memory_pool = nullptr;

#endif //CUSTOM_ALLOCATOR_WRAPPER_H
