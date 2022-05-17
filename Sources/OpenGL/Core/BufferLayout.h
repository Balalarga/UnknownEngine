#pragma once

#include <GL/glew.h>
#include <vector>


struct VariableInfo
{
    unsigned Type;
    unsigned Count;
    unsigned Size;
};

struct BufferLayout
{
    BufferLayout& Float(unsigned count);
    BufferLayout& Int(unsigned count);
    BufferLayout& Unsigned(unsigned count);

    std::vector<VariableInfo> Variables;
    unsigned Size = 0;
};


