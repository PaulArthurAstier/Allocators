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
     * this enum is to select the search mode desired for block reuse.
     */
    enum class search_mode{
        first_fit,
        next_fit,
        best_fit,
    };

    /**
     * the search mode that will be used in block reuse
     */
    search_mode m_search_mode = search_mode::next_fit;

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
      * Sets the used flag of a Chunk to false. By setting the used flag to false, the Chunk is marked to be reused
      * when a new Chunk of memory is being requested.
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

    /**
     * this is for testing purposes, it prints the whole memory linked list and information about each node.
     */
    void print_all_memory();

    /**
     * this is for testing purposes, it prints the number of times the reuse functions go through the list, to see if
     * it becomes more efficient.
     */
    void print_counter() const
    {
        std::cout << "~~~~~~~~~" << std::endl;
        std::cout << "~~~" << counter << "~~~" << std::endl;
        std::cout << "~~~~~~~~~" << std::endl;
    }

private:

    /**
     * align returns the memory needed for the storage of the data. This is specifically made for x64 machines, as it
     * returns 8, 16, 32... etc. This always rounds up, eg(if data is 13 bytes, it will allocate 16 bytes).
     *
     * @param size number of bytes that the user wants to store.
     * @return the round up number of bytes needed to store the data.
     */
    static std::size_t align(std::size_t size);

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
     * Finds the first already allocated Chunk of memory that is not being used. This function goes through the entire
     * linked list of memory, looking for a Chunk that is both not in use (used flag set to false) and has a size bigger
     * than the sized requested. This function does not seek to look for the best size fit for the memory requested.
     *
     * @param size Minimum size being requested
     * @return A pointer to the free, adequate chunk, or nullptr if none were found.
     */
    Chunk* first_fit(std::size_t size);

    /**
     * Works like first_fit(), but when a free Chunk of memory is found, its position is tracked. It is tracked with the
     * member variable m_next_fit_chunk, which is set to m_initial when the Memory_Linked_List is created. When this
     * function is called again, instead of beginning at the start of the Memory_Linked_List, it will continue from the
     * last position tracked, possibly saving some time.
     *
     * @param size the size that is requested for new memory
     * @return a pointer of a freed Chunk, or nullptr if none were found.
     */
    Chunk* next_fit(std::size_t size);

    /**
     *
     *
     * @param size size that is requested for new memory
     * @return a pointer of a freed Chunk, or nullptr if none were found.
     */
    Chunk* best_fit(std::size_t size);

    /**
     * this function chooses which search mode is used for block reuse.
     * @param mode what search mode is used.
     * @param size the memory needed to allocate.
     * @return a pointer the the reused chunk, or a nullptr if there is no available free Chunk.
     */
    Chunk* find_chunk(std::size_t size);

    /** ---------------------------------------------------------------------------------------------------------------
     * Member variables
     */

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

    /**
     *  Used in the next_fit search mode, it keeps track of the last found free chunk
     */
    Chunk* m_next_fit_chunk;

    ///TODO: delete counter member variable after all testing are done.
    int counter;
};

#endif //ALLOCATORSANDMEMORYPOOL_ALLOCATOR_H
