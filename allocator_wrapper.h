#ifndef ALLOCATOR_WRAPPER_H
#define ALLOCATOR_WRAPPER_H

#include <cstddef>
#include <memory>
#include "allocator.h" 

/**
 * A custom memory allocator wrapper class for type T.
 * This class conforms to the C++ standard allocator requirements,
 * allowing it to be used with STL containers.
 */
template <typename T>
class allocator_wrapper
{    
public:
    // Type aliases required for standard allocator interface.
    using value_type = T;                       // The type of object allocated.
    using pointer = T*;                         // Pointer to the allocated type.
    using const_pointer = const T*;             // Pointer to a const version of the allocated type.
    using size_type = std::size_t;              // Type used to specify sizes.
    using difference_type = std::ptrdiff_t;     // Type used to specify pointer differences.

    // Default constructor and destructor.
    allocator_wrapper() noexcept = default;
    ~allocator_wrapper() noexcept = default;

    // Copy constructor template to allow conversion between different allocator types.
    template <typename U>
    allocator_wrapper(const allocator_wrapper<U>&) noexcept {}

    // Allocates memory for a specified number of objects of type T.
    // Uses the custom Memory_Linked_List allocator's alloc() function.
    T* allocate(std::size_t size) noexcept
    {
        // Allocate raw memory using the Memory_Linked_List allocator.
        intptr_t* ptr = mll.alloc(size * sizeof(T));
        return reinterpret_cast<T*>(ptr); // Cast to the appropriate pointer type.
    }

    // Deallocates memory for a single object of type T.
    // Uses the custom Memory_Linked_List allocator's free() function.
    void deallocate(T* data, std::size_t) noexcept
    {
        // Cast back to intptr_t* before freeing the memory.
        mll.free(reinterpret_cast<intptr_t*>(data));
    }

    // Equality operator (required for standard allocators).
    // All instances of this allocator are considered equivalent.
    bool operator==(const allocator_wrapper&) const noexcept { return true; }

    // Inequality operator (required for standard allocators).
    bool operator!=(const allocator_wrapper&) const noexcept { return false; }

    // Rebind struct to allow the allocator to allocate memory for a different type U.
    // This is required for standard allocator compatibility.
    template <typename U>
    struct rebind
    {
        using other = allocator_wrapper<U>; // Defines the rebound allocator type.
    };

private:
    Memory_Linked_List mll{}; // The custom memory allocator instance used for allocation.
};

#endif //ALLOCATOR_WRAPPER_H
