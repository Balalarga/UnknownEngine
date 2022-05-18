#include "IRenderable.h"

#include <assert.h>
#include <iostream>


IRenderable::IRenderable(const Buffer &vbo):
    Vbo(vbo),
    Handler(0),
    ModelMatrix(glm::mat4(1.f))
{
    glGenVertexArrays(1, &Handler);
    glBindVertexArray(Handler);

    unsigned vboId;
    bool vboCreated = Vbo.Create(vboId);

    glBindVertexArray(0);
    if (vboCreated)
        glDeleteBuffers(1, &vboId);
}

IRenderable::~IRenderable()
{
    glDeleteVertexArrays(1, &Handler);
}

void IRenderable::Render()
{
    glBindVertexArray(Handler);
    glDrawArrays(Vbo.DrawType, 0, Vbo.Data.Count);
}

