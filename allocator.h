//
// Created by Paul-Arthur on 08/02/2023.
//

#ifndef ALLOCATOR_H
#define ALLOCATOR_H

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
    Chunk *next;

    /**
     * Payload.
     * Users memory.
     */
    intptr_t data[1];
};

/**
 * A linked list of the chunks created the memory.
 *
 * This whole class is the allocator and memory management class. When creating a new object within the heap, this class
 * will create memory and manage it.
 */
class Memory_Linked_List
{
public:
    /**
     * this enum is to select the search mode desired for block reuse.
     *
     * first_fist will reuse the first block that is big enough to store the data.
     *
     * next_fit is like first_fit, but will keep the position of the last tracked found memory, so it doesnt have to
     * start all over again.
     *
     * best_fit will find the best block possible for the new memory.
     *
     * free_list creates a new linked list of the free Chunks, and will go through that list when reusing memory .
     */
    enum class search_mode
    {
        first_fit,
        next_fit,
        best_fit,
        free_list,
    };

    enum class mmap_mode
    {
        sbrk,
        mmap,
    };

    /**
     * the search mode that will be used in block reuse
     */
    search_mode m_search_mode = search_mode::first_fit;

    /**
     * the allocator chosen when allocating
     */
    mmap_mode m_mmap_mode = mmap_mode::mmap;

    void set_search_mode(search_mode mode); // Declaration for setting searchmode for benchmark test

    /**
     * Initialises the link list. It sets all of the member variables to nullptr.
     */
    Memory_Linked_List();

    /**
     *  alloc memory onto the heap, manging this memory in a linked list, and creating or recycling Chunks.
     *
     *  alloc will first check if there are any Chunks that can be recycled first, using what ever algorithm is
     *  selected in m_search_mode. If a free Chunk as not been found, it will manually request memory form the heap.
     *  alloc also manages the memory linked list, initializing it or adding new chunks at the end of it. In either
     *  cases, whether a Chunk is recycled or created, the Chunk used value is set to true and the payload pointer is
     *  returned to the user.
     * @param size the size that the user wants to store.
     * @return the payload pointer to the data.
     */
    intptr_t *alloc(std::size_t size);

    /**
     * Sets the used flag of a Chunk to false.
     *
     * By setting the used flag to false, the Chunk is marked to be reused when a new Chunk of memory is being
     * requested. If the free_list option has been selected, it will instead put the freed chunk in its own linked list
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
    static Chunk *get_header(intptr_t *data)
    {
        return (Chunk *)((char *)data + sizeof(std::declval<Chunk>().data) - sizeof(Chunk));
    }

    /**
     * this is for testing purposes, it prints the whole memory linked list and information about each node.
     */
    void print_all_memory();

    /**
     * prints all the memory as int
     */
    void print_all_memory_as_int();

    /**
     * prints all the memory as char
     */
    void print_all_memory_as_char();

    /**
     * this is for testing purposes, it prints the whole freed memory linked list and information about each node.
     */
    void print_all_free_memory();

    /**
     * A default destructor to give memory back to the OS when the class is not used anymore.
     */
    ~Memory_Linked_List() = default;

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
     * This function simply selects the allocator, etheir sbrk or mmap.
     * 
     * @param size The amount of bytes that the user wants to store
     */
    Chunk* memory_map(std::size_t size);

    /**
     * The mmap allocator.
     * returns the program break pointer (heap pointer) and makes sure that it will not go out of memory (OOM). It
     * returns the program break, and it also does a check if it is possible to allocate this chunk, and if it is not
     * possible, to returns nullptr.
     *
     * @param size amount of bytes that needs to be stored.
     * @return the program break pointer.
     */
    Chunk *memory_map_mmap(std::size_t size);

    /**
     * The sbrk allocator.
     * returns the program break pointer (heap pointer) and makes sure that it will not go out of memory (OOM). It
     * returns the program break, and it also does a check if it is possible to allocate this chunk, and if it is not
     * possible, to returns nullptr.
     *
     * @param size amount of bytes that needs to be stored.
     * @return the program break pointer.
     */
    Chunk *memory_map_sbrk(std::size_t size);

    /**
     * Finds the first already allocated Chunk of memory that is not being used. This function goes through the entire
     * linked list of memory, looking for a Chunk that is both not in use (used flag set to false) and has a size bigger
     * than the sized requested. This function does not seek to look for the best size fit for the memory requested.
     *
     * @param size Minimum size being requested
     * @return A pointer to the free, adequate chunk, or nullptr if none were found.
     */
    Chunk *first_fit(std::size_t size);

    /**
     * Works like first_fit(), but when a free Chunk of memory is found, its position is tracked. It is tracked with the
     * member variable m_next_fit_chunk, which is set to m_initial when the Memory_Linked_List is created. When this
     * function is called again, instead of beginning at the start of the Memory_Linked_List, it will continue from the
     * last position tracked, possibly saving some time.
     *
     * @param size the size that is requested for new memory
     * @return a pointer of a freed Chunk, or nullptr if none were found.
     */
    Chunk *next_fit(std::size_t size);

    /**
     * best_fit() will seek the best possible Chunk in terms of size.
     *
     * best_fit() will first go through the whole list checking if there is a freed Chunk big enough for it. If there
     * are none, then it will return nullptr. It will start with the minimum size required and go through the whole list.
     * If there is no chunk freed with said size is found, do it again but with double the size required. This will
     * continue until a Chunk is found.
     *
     * @param size size that is requested for new memory
     * @return a pointer of a freed Chunk, or nullptr if none were found.
     */
    Chunk *best_fit(std::size_t size);

    /**
     *  Creates and manges a linked list for free Chunks.
     *
     *  free_listing will add Chunks to a free linked list, initializing it if there are none, or adding them to the end
     *  of the list. It also removes the freed Chunk for the memory linked list. This makes searching much faster, as
     *  the reuse algorithm only has to go through the freed Chunks.
     *
     * @param chunk the Chunk being removed.
     */
    void free_listing(Chunk *chunk);

    /**
     * Reuses Chunks from the freed list, and moving them to the memory linked list.
     *
     * This does the opposite of free_listing. It also checks if there is enough memory for the data requested.
     *
     * @param size the size needed for memory
     * @return the chunk that is being reused.
     */
    Chunk *free_list(std::size_t size);

    /**
     * this function chooses which search mode is used for block reuse.
     * @param mode what search mode is used.
     * @param size the memory needed to allocate.
     * @return a pointer the the reused chunk, or a nullptr if there is no available free Chunk.
     */
    Chunk *find_chunk(std::size_t size);

    /** ---------------------------------------------------------------------------------------------------------------
     * Member variables
     */

    /**
     * initial start of the linked list
     */
    Chunk *m_initial;
    /**
     * The start of the linked list.
     */
    Chunk *m_start;
    /**
     * The end of the linked list.
     */
    Chunk *m_end;

    /**
     * Used in the next_fit search mode, it keeps track of the last found free chunk
     */
    Chunk *m_next_fit_chunk;

    /**
     * initial Chunk in the freed list
     */
    Chunk *f_list_initial;

    /**
     * the first Chunk in the freed list
     */
    Chunk *f_list_start;

    /**
     * the last Chunk in the freed list
     */
    Chunk *f_list_end;
};

#endif //ALLOCATOR_H
