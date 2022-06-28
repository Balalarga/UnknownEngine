#include "IRenderable.h"

#include <iostream>
#include <glm/gtc/matrix_transform.hpp>

#include "OpenGL/ErrorHandle.h"


IRenderable::IRenderable(const Buffer &vbo):
    _handler(0)
{
    Setup(vbo);
}

IRenderable::~IRenderable()
{
    Release();
    GLCall(glDeleteVertexArrays(1, &_handler))
}

void IRenderable::Render()
{
    if ( !_bVisible )
        return;
    
    Bind();
    GLCall(glDrawArrays(_vbo.DrawType, 0, _vbo.Data.Count))
}

bool IRenderable::Setup(const Buffer& vbo)
{
    if (!vbo.Data.Ptr)
        return false;
    
    _vbo = vbo;
    
    GLCall(glGenVertexArrays(1, &_handler))
    GLCall(glBindVertexArray(_handler))

    unsigned vboId = _vbo.Create();
    GLCall(glBindVertexArray(0))
    
    if (vboId == 0)
        return false;
    
    GLCall(glDeleteBuffers(1, &vboId))
    return true;
}

void IRenderable::SetShader(Shader* shader)
{
    if (_shaderPtr)
        _shaderPtr->DetachFrom(this);
    
    _shaderPtr = shader;
    
    shader->AttachTo(this);
}

void IRenderable::Bind()
{
    GLCall(glBindVertexArray(_handler))
}

void IRenderable::Release()
{
    GLCall(glBindVertexArray(0))
}

void IRenderable::Move(const glm::fvec3 dPos)
{
    _pos += dPos;
    UpdateModelMatrix();
}

void IRenderable::MoveTo(const glm::fvec3 newPos)
{
    _pos = newPos;
    UpdateModelMatrix();
}

void IRenderable::ScaleTo(const glm::fvec3& newScale)
{
    _scale = newScale;
    UpdateModelMatrix();
}

void IRenderable::Scale(const glm::fvec3& dScale)
{
    _scale += dScale;
    UpdateModelMatrix();
}

void IRenderable::RotateTo(const glm::fvec3& newRotation)
{
    _rotation = newRotation;
    UpdateModelMatrix();
}

void IRenderable::Rotate(const glm::fvec3& dRotation)
{
    _rotation += dRotation;
    UpdateModelMatrix();
}

void IRenderable::UpdateModelMatrix()
{
    constexpr float toRadians = 1.f / 180.f * 3.141592653589793238463f;
    
    _modelMatrix = translate(glm::mat4(1.0f), _pos);
    _modelMatrix = scale(_modelMatrix, _scale);
    _modelMatrix = rotate(_modelMatrix, toRadians * _rotation.x, {1, 0, 0});
    _modelMatrix = rotate(_modelMatrix, toRadians * _rotation.y, {0, 1, 0});
    _modelMatrix = rotate(_modelMatrix, toRadians * _rotation.z, {0, 0, 1});
}
