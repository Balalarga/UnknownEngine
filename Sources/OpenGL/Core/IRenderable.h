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

    void SetShader(const std::shared_ptr<Shader>& shader);

    virtual void Render();


    inline Shader* GetShader() { return Shader.get(); }


private:
    Buffer Vbo;
    std::shared_ptr<Shader> Shader;

    unsigned Handler;
    glm::mat4 ModelMatrix;
};

#endif // RENDERABLE_H
