#pragma once

#include <map>
#include <string>
#include <vector>

#include <GL/glew.h>
#include <glm/glm.hpp>


class Shader
{
public:
    Shader(const std::string& vertexCode,
           const std::string& fragmentCode,
           const std::string& geomertyCode = "");
    virtual ~Shader();

    bool UpdateVertexShader(const std::string &code);
    bool UpdateFragmentShader(const std::string &code);
    bool UpdateGeomertyShader(const std::string &code);

    bool AddUniform(const std::string& name);
    bool AddUniforms(const std::vector<std::string>& names);

    int GetUniformLoc(const std::string& name);

    bool Compile();

    void Bind() const;
    void Unbind() const;


    void SetUniform(const std::string& name, const int& value);
    void SetUniform(const std::string& name, const float& value);
    void SetUniform(const std::string& name, const glm::vec2& value);
    void SetUniform(const std::string& name, const glm::vec3& value);
    void SetUniform(const std::string& name, const glm::vec4& value);
    void SetUniform(const std::string& name, const glm::mat4& value);
    void SetUniform(const std::string& name, const glm::mat3& value);


protected:
    void Destroy();
    bool HasErrors(unsigned shaderId);


private:
    std::string VertexCode;
    std::string FragmentCode;
    std::string GeometryCode;
    std::map<std::string, int> Uniforms;

    GLuint Handler;
};

