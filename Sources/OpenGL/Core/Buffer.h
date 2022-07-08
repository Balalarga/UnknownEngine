#pragma once


#include "BufferLayout.h"
#include "DataPtr.h"


struct Buffer
{
    Buffer(const DataPtr& data = {}, const BufferLayout& layout = BufferLayout());

    DataPtr Data;
    BufferLayout Layout;
    unsigned DrawType = GL_TRIANGLES;
    unsigned Type = GL_ARRAY_BUFFER;
    unsigned Mode = GL_STATIC_DRAW;

    unsigned Create();
};
