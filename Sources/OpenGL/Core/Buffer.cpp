#include "Buffer.h"



DataPtr::DataPtr():
    Ptr(nullptr),
    Count(0),
    ItemSize(0)
{
    
}

DataPtr::DataPtr(void* ptr, unsigned count, unsigned itemSize):
    Ptr(ptr),
    Count(count),
    ItemSize(itemSize)
{

}

Buffer::Buffer(const DataPtr& data, const BufferLayout& layout):
    Data(data),
    Layout(layout)
{

}

bool Buffer::Create(unsigned& handler)
{
    if (!Data.Ptr)
        return false;

    glGenBuffers(1, &handler);
    glBindBuffer(Type, handler);
    glBufferData(Type, Data.Count * Data.ItemSize, Data.Ptr, Mode);

    size_t offset = 0;
    for (size_t i = 0; i < Layout.Variables.size(); ++i)
    {
        glEnableVertexAttribArray(i);
        glVertexAttribPointer(i,
                              Layout.Variables[i].Count,
                              Layout.Variables[i].Type,
                              Layout.Variables[i].Normalized ? GL_FALSE : GL_TRUE,
                              Layout.Size,
                              (void*)offset);
        offset += Layout.Variables[i].Size * Layout.Variables[i].Count;
    }
    return true;
}
