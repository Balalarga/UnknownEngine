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


bool Buffer::Create(unsigned& handler)
{
    if (!Data.Ptr)
        return false;

    glGenBuffers(1, &handler);
    glBindBuffer(Type, handler);
    glBufferData(Type, Data.ItemSize * Data.ItemSize, Data.Ptr, Mode);

    size_t offset = 0;
    for (size_t i = 0; i < Layout.Variables.size(); ++i)
    {
        const auto& item = Layout.Variables[i];
        glEnableVertexAttribArray(i);
        glVertexAttribPointer(i,
                              Layout.Variables[i].Count,
                              Layout.Variables[i].Type,
                              GL_FALSE,
                              Layout.Size,
                              (void*)&offset);
        offset += item.Size;
    }
    return true;
}
