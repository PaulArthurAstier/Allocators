//
// Created by Paul-Arthur on 08/02/2023.
//

#include <utility>
#include <sys/mman.h>  
#include <unistd.h>
#include <iostream>
#include "allocator.h"

Memory_Linked_List::Memory_Linked_List():
        m_initial{nullptr},
        m_start{m_initial},
        m_next_fit_chunk{nullptr},
        m_end{nullptr},
        f_list_initial{nullptr},
        f_list_start{nullptr},
        f_list_end{nullptr}
{}

intptr_t *Memory_Linked_List::alloc(std::size_t size)
{
    //gets the minimum memory needed for allocation
    auto aligned = align(size);

    //looks for chunks that are freed

    if(auto freed_chunk = find_chunk(aligned))
    {
        //sets free chunk flag to used
        freed_chunk->used = true;
        //gives a pointer to the freed chunk
        return freed_chunk->data;
    }

    //requests data from memory
    auto chunk = memory_map(aligned);

    //sets its header
    chunk->size = aligned;
    chunk->used = true;

    //linking chunk to the list
    if(m_start != nullptr)
    {
        m_end->next = chunk;
    }

    //initialises the list
    if(m_initial == nullptr)
    {
        m_initial = chunk;
        m_next_fit_chunk = chunk;
        m_start = chunk;
    }

    //making chunk the last on the list
    m_end = chunk;

    //returning a pointer to the data
    return chunk->data;
}

std::size_t Memory_Linked_List::align(std::size_t size)
{
    //minimum data size is 8
    auto i = 8;

    //doubles until minimum size required is reached
    while (i < size)
    {
        i *= 2;
    }
    return i;
}

std::size_t Memory_Linked_List::allocSize(std::size_t size)
{
    //size of data + size of header - initial data
    return size + sizeof(Chunk) - sizeof(std::declval<Chunk>().data);
}

Chunk *Memory_Linked_List::memory_map(std::size_t size)
{
    // Calculate the allocation size, including any metadata and alignment requirements
    std::size_t total_size = allocSize(size);

    // Use mmap to allocate memory with read/write permissions
    void* addr = mmap(nullptr, total_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

    // Check if mmap failed
    if (addr == MAP_FAILED)
    {
        return nullptr;
    }

    return static_cast<Chunk*>(addr);
}

void Memory_Linked_List::free(intptr_t *data)
{
    //gets chunk that is being freed
    auto chunk = get_header(data);

    //if free_list mode is set, the freed data will be put in its own linked list
    if(m_search_mode == search_mode::free_list)
    {
        free_listing(chunk);
    }

    //frees it
    chunk->used = false;
}

Chunk* Memory_Linked_List::free_list(std::size_t size)
{
    Chunk* prev_s{m_initial};

    for(auto s = f_list_initial; s != nullptr; s = s->next)
    {
        if(s->size >= size)
        {
            if(s == f_list_initial)
            {
                if(f_list_initial->next == nullptr)
                {
                    //add to the free list if it exists
                    if(m_initial != nullptr)
                    {
                        m_end->next = s;
                    }
                    //initialise the free list
                    if(m_initial == nullptr)
                    {
                        m_initial = s;
                        m_start = s;
                    }

                    //makes the chunk the last in the list
                    s->next = nullptr;
                    m_end = s;

                    //reset the whole mll
                    f_list_initial = nullptr;
                    f_list_start = nullptr;
                    f_list_end = nullptr;

                    return s;
                }
                else
                {
                    f_list_initial = s->next;
                    f_list_start = s->next;

                    //adds chunk to the free list
                    if (m_initial != nullptr)
                    {
                        m_end->next = s;
                    }
                    //initialise the free list
                    if (m_initial == nullptr)
                    {
                        m_initial = s;
                        m_start = s;
                    }

                    //adds chunk to the end of the list
                    s->next = nullptr;
                    m_end = s;
                    return s;
                }
            }
            else
            {
                if(s == m_end)
                {
                    m_end  = prev_s;
                    prev_s->next = nullptr;
                }
                else
                {
                    prev_s->next = s->next;
                }

                //adds chunk to the free list
                if (m_initial != nullptr)
                {
                    m_end->next = s;
                    s->next = nullptr;
                }
                //initialise the free list
                if (m_initial == nullptr)
                {
                    m_initial = s;
                    m_start = s;
                }
                s->next = nullptr;
                f_list_end = s;
            }
        }
        prev_s = s;
    }
    return nullptr;
}

void Memory_Linked_List::free_listing(Chunk* chunk)
{
    //checks if the first one is the chunk
    if(chunk == m_initial)
    {
        //checks if the mll is only one chunk
        if(chunk->next == nullptr)
        {
            //add to the free list if it exists
            if(f_list_start != nullptr)
            {
                f_list_end->next = chunk;
            }
            //initialise the free list
            if(f_list_initial == nullptr)
            {
                f_list_initial = chunk;
                f_list_start = chunk;
            }

            //makes the chunk the last in the list
            f_list_end = chunk;

            //reset the whole mll
            m_initial = nullptr;
            m_start = nullptr;
            m_end = nullptr;
        }

        //chunk is first, but not last in the mll
        else
        {
            //update the current mll
            m_initial = chunk->next;
            m_start = chunk->next;

            //adds chunk to the free list
            if (f_list_start != nullptr)
            {
                f_list_end->next = chunk;
            }
            //initialise the free list
            if (f_list_initial == nullptr)
            {
                f_list_initial = chunk;
                f_list_start = chunk;
            }

            //adds chunk to the end of the list
            chunk->next = nullptr;
            f_list_end = chunk;
        }
    }

    //keeping track of the last chunk
    Chunk* prev_s{m_initial};

    for(auto s = m_initial; s != nullptr; s = s->next)
    {
        if(s == chunk)
        {
            if(chunk == m_end)
            {
                m_end  = prev_s;
                prev_s->next = nullptr;
            }
            else
            {
                prev_s->next = chunk->next;
            }

            //adds chunk to the free list
            if (f_list_start != nullptr)
            {
                f_list_end->next = chunk;
                chunk->next = nullptr;
            }
            //initialise the free list
            if (f_list_initial == nullptr)
            {
                f_list_initial = chunk;
                f_list_start = chunk;
            }
            chunk->next = nullptr;
            f_list_end = chunk;
        }
        prev_s = s;
    }
}

Chunk *Memory_Linked_List::first_fit(std::size_t size)
{
    //going through the whole list
    for(auto s = m_initial; s != nullptr; s = s->next)
    {
        //checks if it is an adequate free Chunk
        if(!s->used && s->size >= size)
        {
            return s;
        }
    }
    //if nothing found, return null
    return nullptr;
}

Chunk *Memory_Linked_List::next_fit(std::size_t size)
{
    //going through the whole list, but starting at the last found block
    for(auto s = m_next_fit_chunk; s != nullptr; s = s->next)
    {
        //checking if block reuse conditions are met
        if(!s->used && s->size >= size)
        {
            //resetting the m_next_fit_chunk to the start if it is at the end of the list
            if(m_next_fit_chunk == nullptr)
            {
                m_next_fit_chunk = m_initial;
            }
            //making m_next_fit_chunk the latest found chunk
            else m_next_fit_chunk = s;
            return s;
        }
    }
    return nullptr;
}

Chunk *Memory_Linked_List::best_fit(std::size_t size)
{
    int multiplier {1};
    size_t max_memory_stored {0};

    //go through the whole list, saving the largest stored size of a chunk
    for(auto s = m_initial; s != nullptr; s = s->next)
    {
        if(max_memory_stored < s->size)
            max_memory_stored = s->size;
    }

    //if size is bigger then the largest stored chunk, return nullptr
    if(size > max_memory_stored)
        return nullptr;

    //start with the minimum size required and go through the whole list. If there is no chunk freed with said size is
    //found, do it again but with double the size required.
    while(true)
    {
        for(auto s = m_initial; s != nullptr; s = s->next)
        {
            if (!s->used && s->size == size * multiplier)
            {
                return s;
            }
        }
        if(size * multiplier == max_memory_stored)
            return nullptr;

        multiplier *= 2;
    }
}

Chunk *Memory_Linked_List::find_chunk(std::size_t size)
{
    switch (m_search_mode)
    {
        case search_mode::first_fit:
            return first_fit(size);
            break;
        case search_mode::next_fit:
            return next_fit(size);
            break;
        case search_mode::best_fit:
            return best_fit(size);
            break;
        case search_mode::free_list:
            return free_list(size);
        default:
            throw std::invalid_argument("No search mode were selected");
            return nullptr;
    }
}

void Memory_Linked_List::print_all_memory()
{
    // go through the whole list
    for(auto i = m_initial; i != nullptr; i = i->next)
    {
        std::cout << "---------------------" << std::endl;
        std::cout << "payload : " << (char)i->data[0] << std::endl;
        std::cout << "size:     " << i->size << std::endl;
        std::cout << "Used:     " << i->used << std::endl;
    }
}

void Memory_Linked_List::print_all_free_memory()
{
    // go through the whole list
    for(auto i = f_list_initial; i != nullptr; i = i->next)
    {
        std::cout << "---------------------" << std::endl;
        std::cout << "payload : " << (char)i->data[0] << std::endl;
        std::cout << "size:     " << i->size << std::endl;
        std::cout << "Used:     " << i->used << std::endl;
    }
}
