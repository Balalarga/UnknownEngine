#ifndef RENDERABLE_H
#define RENDERABLE_H

#include <vector>
#include <memory>
#include <GL/glew.h>

#include "Shader.h"
#include "Buffer.h"


class IRenderable
{
public:
    IRenderable(const Buffer& vbo);
    virtual ~IRenderable();

    virtual void Render();

    void SetShader(std::shared_ptr<Shader> shader) { ShaderPtr = shader; }
    inline Shader* GetShader() { return ShaderPtr.get(); }


private:
    Buffer Vbo;
    GLuint Handler;
    std::shared_ptr<Shader> ShaderPtr;

    glm::mat4 ModelMatrix;
};

#endif // RENDERABLE_H
