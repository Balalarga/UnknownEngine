#pragma once


#include "BufferLayout.h"


struct DataPtr
{
    DataPtr();
    DataPtr(void* Ptr = nullptr, unsigned Count = 0, unsigned ItemSize = 0);

    void* Ptr;
    unsigned Count;
    unsigned ItemSize;
};

struct Buffer
{
    DataPtr Data;

    BufferLayout Layout = BufferLayout().Float(3).Float(4);

    unsigned DrawType = GL_TRIANGLES;
    unsigned Type = GL_ARRAY_BUFFER;
    unsigned Mode = GL_STATIC_DRAW;

    bool Create(unsigned& handler);
};
