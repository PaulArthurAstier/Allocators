//
// Created by Paul-Arthur on 08/02/2023.
//

#include <utility>
#include <unistd.h>
#include "allocator.h"

Memory_Linked_List::Memory_Linked_List():
        m_initial{nullptr},
        m_start{m_initial}
{}

intptr_t *Memory_Linked_List::alloc(std::size_t size)
{
    //maps the chunk
    auto aligned = align(size);
    auto chunk = memory_map(aligned);

    //sets its header
    chunk->size = aligned;
    chunk->used = true;

    //initialises the list
    if(m_initial == nullptr)
    {
        m_initial = chunk;
    }

    //linking chunk to the list
    else if(m_start != nullptr)
    {
        m_end->next = chunk;
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
