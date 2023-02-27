//
// Created by Paul-Arthur on 08/02/2023.
//

#ifndef ALLOCATORSANDMEMORYPOOL_ALLOCATOR_H
#define ALLOCATORSANDMEMORYPOOL_ALLOCATOR_H

#include <cstdint>

/**
 * Chunk is a node within the memory pool link list.
 *
 * Chunk has a payload pointer that points towards the users data. The rest is the header, which determines whether it
 * is used, how big it is, and what the next node is.
 */
class Chunk
{
public:
    /**
     * Header.
     * Size of the chunk.
     */
    std::size_t size;

    /**
     * checking if it is used.
     */
    bool used;

    /**
     * pointer to next chunk.
     */
    Chunk* next;

    /**
     * Payload.
     * Users memory.
     */
    intptr_t data[1];
};

/**
 * A linked list of the chunks created the memory.
 *
 *
 */
class Memory_Linked_List
{
public:
    /**
     * Initialises the link list. It sets m_initial to nullptr, and m_start to m_initial.
     */
    Memory_Linked_List();

    /**
     *
     * @param size
     * @return
     */
     intptr_t* alloc(std::size_t size);

     /**
      * Sets the used flag of a Chunk to false.
      *
      * @param data a pointer of the memory that is being freed.
      */
     void free(intptr_t *data);

    /**
     *  Returns a Chunk within the memory.
     *
     * @param data the pointer of the memory stored.
     * @return a pointer of the header of the chunk.
     *
     * @note This function is copied from Writing a Memory Allocator by Dmitry Soshnikov, as I am not exactly sure how
     * it works. Link (http://dmitrysoshnikov.com/compilers/writing-a-memory-allocator/).
     */
    static Chunk* get_header(intptr_t* data)
    {
        return (Chunk*)((char*)data + sizeof(std::declval<Chunk>().data) - sizeof(Chunk));
    }

private:

    /**
     * align returns the memory needed for the storage of the data. This is specifically made for x64 machines, as it
     * returns 8, 16, 32... etc. This always rounds up, eg(if data is 13 bytes, it will allocate 16 bytes).
     *
     * @param size number of bytes that the user wants to store.
     * @return the round up number of bytes needed to store the data.
     */
    std::size_t align(std::size_t size);

    /**
     * Returns the size of the data that needs to be allocated, plus the size of the header. The header however,
     * already has the first pointer of the user data, so it is subtracted.
     *
     * @param size the number of bytes that is being allocated.
     * @return the size plus the header.
     *
     * @note This function is copied from Writing a Memory Allocator by Dmitry Soshnikov, as I am not exactly sure how
     * it works. Link (http://dmitrysoshnikov.com/compilers/writing-a-memory-allocator/).
     */
    std::size_t allocSize(std::size_t size);

    /**
     * returns the program break pointer (heap pointer) and makes sure that it will not go out of memory (OOM). It
     * returns the program break, and it also does a check if it is possible to allocate this chunk, and if it is not
     * possible, to returns nullptr.
     *
     * @param size amount of bytes that needs to be stored.
     * @return the program break pointer.
     */
    Chunk* memory_map(std::size_t size);

    /**
     * initial start of the linked list
     */
    Chunk* m_initial;
    /**
     * The start of the linked list.
     */
    Chunk* m_start;
    /**
     * The end of the linked list.
     */
    Chunk* m_end;
};

#endif //ALLOCATORSANDMEMORYPOOL_ALLOCATOR_H
