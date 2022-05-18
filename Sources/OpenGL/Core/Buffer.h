#pragma once


#include "BufferLayout.h"


struct DataPtr
{
    DataPtr();
    DataPtr(void* Ptr, unsigned Count, unsigned ItemSize);

    void* Ptr;
    unsigned Count;
    unsigned ItemSize;
};

struct Buffer
{
    Buffer(const DataPtr& data, const BufferLayout& layout = BufferLayout());

    DataPtr Data;
    BufferLayout Layout;
    unsigned DrawType = GL_TRIANGLES;
    unsigned Type = GL_ARRAY_BUFFER;
    unsigned Mode = GL_STATIC_DRAW;

    bool Create(unsigned& handler);
};
