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
    IRenderable(const Buffer& vbo = {});
    virtual ~IRenderable();

    virtual void Render();

    bool Setup(const Buffer& vbo);
    
    void SetShader(Shader* shader);
    Shader* GetShader() { return _shaderPtr; }
    
    void Bind();
    void Release();

    void SetVisible(bool bVisible) { _bVisible = bVisible; }

    void Move(const glm::fvec3 dPos);
    void MoveTo(const glm::fvec3 newPos);
    const glm::fvec3& GetPosition() const { return _pos; }

    void ScaleTo(const glm::fvec3& newScale);
    void Scale(const glm::fvec3& dScale);
    const glm::fvec3& GetScale() const { return _scale; }
    
    void RotateTo(const glm::fvec3& newRotation);
    void Rotate(const glm::fvec3& dRotation);
    const glm::fvec3& GetRotation() const { return _rotation; }

    const glm::fmat4& GetModelMatrix() const { return _modelMatrix; }
    
    
protected:
    void UpdateModelMatrix();
    
    
private:
    bool _bVisible = true;
    
    Buffer _vbo;
    GLuint _handler;
    Shader* _shaderPtr{};

    glm::fvec3 _pos{0};
    glm::fvec3 _scale{1};
    glm::fvec3 _rotation{0};
    glm::fmat4 _modelMatrix{1};
};

#endif // RENDERABLE_H
