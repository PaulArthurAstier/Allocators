//
// Created by Paul-Arthur on 08/02/2023.
//

#include <utility>
#include <unistd.h>
#include <iostream>
#include "allocator.h"

Memory_Linked_List::Memory_Linked_List():
        m_initial{nullptr},
        m_start{m_initial}
{}

intptr_t *Memory_Linked_List::alloc(std::size_t size)
{
    //gets the minimum memory needed for allocation
    auto aligned = align(size);

    //looks for chunks that are freed
    if(auto freed_chunk = find_chunk(size))
    {
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
    //program break
    auto chunk = (Chunk*)sbrk(0);

    //check if it will be OOM
    if(sbrk(allocSize(size)) == (void*)-1 )
    {
        return nullptr;
    }
    return chunk;
}

void Memory_Linked_List::free(intptr_t *data)
{
    //gets chunk that is being freed
    auto chunk = get_header(data);
    //frees it
    chunk->used = false;
}

Chunk *Memory_Linked_List::first_fit(std::size_t size)
{
    //start searching at the top of the linked list
    auto search = m_initial;

    //goes through the whole list
    while (search != nullptr)
    {
        //checks if it is not used and has adequate size
        if(!search->used && search->size > size)
        {
            return search;
        }
        //if not, continue search
        search = search->next;
    }
    //if nothing found, return null
    return nullptr;
}

Chunk *Memory_Linked_List::find_chunk(std::size_t size)
{
    return first_fit(size);
}

void Memory_Linked_List::print_all_memory()
{
    for(auto i = m_initial; i != nullptr; i = i->next)
    {
        std::cout << "data: " << *i->data << std::endl;
        std::cout << "size: " << i->size << std::endl;
        std::cout << "Used: " << i->used << std::endl;
        std::cout << "Pointer of itself: " << &i->data << std::endl;
        std::cout << "Next chunk pointer: " << i->next << std::endl;
        std::cout << "---------------------" << std::endl;
    }
}
