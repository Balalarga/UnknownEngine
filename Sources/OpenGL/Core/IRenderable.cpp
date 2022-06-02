#include "IRenderable.h"

#include <assert.h>
#include <iostream>

#include "OpenGL/ErrorHandle.h"


IRenderable::IRenderable(const Buffer &vbo):
    Vbo(vbo),
    Handler(0),
    ModelMatrix(glm::mat4(1.f))
{
    GLCall(glGenVertexArrays(1, &Handler))
    GLCall(glBindVertexArray(Handler))

    unsigned vboId;
    bool vboCreated = Vbo.Create(vboId);

    GLCall(glBindVertexArray(0))
    if (vboCreated)
        GLCall(glDeleteBuffers(1, &vboId))
}

IRenderable::~IRenderable()
{
    Release();
    GLCall(glDeleteVertexArrays(1, &Handler))
}

void IRenderable::Render()
{
    Bind();
    GLCall(glDrawArrays(Vbo.DrawType, 0, Vbo.Data.Count))
}

void IRenderable::Bind()
{
    GLCall(glBindVertexArray(Handler))
}

void IRenderable::Release()
{
    GLCall(glBindVertexArray(0))
}
