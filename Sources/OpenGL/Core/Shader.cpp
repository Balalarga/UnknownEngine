#include "Shader.h"

#include <vector>
#include <iostream>

#include "OpenGL/ErrorHandle.h"


Shader::Shader(const std::string &vertexCode,
               const std::string &fragmentCode,
               const std::string &geomertyCode):
    VertexCode(vertexCode),
    FragmentCode(fragmentCode),
    GeometryCode(geomertyCode),
    Handler(0)
{
    Compile();
}

bool Shader::HasErrors(unsigned shaderId)
{
    GLint isCompiled = 0;
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &isCompiled);
    if(isCompiled == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &maxLength);

        std::vector<GLchar> errorLog(maxLength);
        glGetShaderInfoLog(shaderId, maxLength, &maxLength, &errorLog[0]);
        for(auto i: errorLog)
        {
            std::cout<<i;
        }
        std::cout<<std::endl;

        return true;
    }
    return false;
}

void Shader::Destroy()
{
    Unbind();
    GLCall(glDeleteProgram(Handler))
}

Shader::~Shader()
{
    Destroy();
}

bool Shader::AddUniform(const std::string &name)
{
    Bind();
    int loc = glGetUniformLocation(Handler, name.c_str());
    if (loc < 0)
    {
        Unbind();
        return false;
    }

    Uniforms[name] = loc;

    Unbind();
    return true;
}

bool Shader::AddUniforms(const std::vector<std::string> &names)
{
    Bind();
    bool allOk = true;
    for (auto& name : names)
    {
        int loc = glGetUniformLocation(Handler, name.c_str());

        if (loc < 0)
        {
            std::cout << "Couldn't find "<< name << " uniform\n";
            allOk = false;
        }
        else
        {
            Uniforms[name] = loc;
        }
    }

    Unbind();
    return allOk;
}


bool Shader::Compile()
{
    std::vector<std::pair<unsigned, const std::string&>> shaders
    {
        {GL_VERTEX_SHADER, VertexCode},
        {GL_FRAGMENT_SHADER, FragmentCode},
        {GL_GEOMETRY_SHADER, GeometryCode},
    };

    Handler = glCreateProgram();

    std::vector<unsigned> attachedShaders;
    for (auto& [type, code]: shaders)
    {
        if (code.empty())
            continue;

        const unsigned id = glCreateShader(type);
        const char* rawSource = code.c_str();

        GLCall(glShaderSource(id, 1, &rawSource, 0))
        GLCall(glCompileShader(id))

        if (HasErrors(id))
        {
            std::cout << "Shader compilation error\n" << code << std::endl;
            glDeleteShader(id);
            for(auto& i: attachedShaders)
            {
                glDetachShader(Handler, i);
                glDeleteShader(i);
            }

            Destroy();
            return false;
        }

        attachedShaders.push_back(id);
        GLCall(glAttachShader(Handler, id))
    }

    GLCall(glLinkProgram(Handler))

    for (auto& i: attachedShaders)
    {
        GLCall(glDetachShader(Handler, i))
        GLCall(glDeleteShader(i))
    }
    return true;
}

void Shader::Bind() const
{
    GLCall(glUseProgram(Handler))
}

void Shader::Unbind() const
{
    GLCall(glUseProgram(0))
}

bool Shader::UpdateVertexShader(const std::string& code)
{
    Destroy();
    VertexCode = code;
    return Compile();
}

bool Shader::UpdateFragmentShader(const std::string& code)
{
    Destroy();
    FragmentCode = code;
    return Compile();
}

bool Shader::UpdateGeomertyShader(const std::string& code)
{
    Destroy();
    GeometryCode = code;
    return Compile();
}

void Shader::SetUniform(const std::string &name, const int &value)
{
    int loc = GetUniformLoc(name);
    if (loc >= 0)
    {
        GLCall(glUniform1i(loc, value))
    }
}

void Shader::SetUniform(const std::string &name, const float &value)
{
    int loc = GetUniformLoc(name);
    if (loc >= 0)
    {
        GLCall(glUniform1f(loc, value))
    }
}

void Shader::SetUniform(const std::string &name, const glm::vec2 &value)
{
    int loc = GetUniformLoc(name);
    if (loc >= 0)
    {
        GLCall(glUniform2f(loc, value.x, value.y))
    }
}

void Shader::SetUniform(const std::string &name, const glm::vec3 &value)
{
    int loc = GetUniformLoc(name);
    if (loc >= 0)
    {
        GLCall(glUniform3f(loc, value.x, value.y, value.z))
    }
}

void Shader::SetUniform(const std::string &name, const glm::vec4 &value)
{
    int loc = GetUniformLoc(name);
    if (loc >= 0)
    {
        GLCall(glUniform4f(loc, value.x, value.y, value.z, value.w))
    }
}

void Shader::SetUniform(const std::string &name, const glm::mat4 &value)
{
    int loc = GetUniformLoc(name);
    if (loc >= 0)
    {
        GLCall(glUniformMatrix4fv(loc, 1, GL_FALSE, &value[0][0]))
    }
}

void Shader::SetUniform(const std::string &name, const glm::mat3 &value)
{
    int loc = GetUniformLoc(name);
    if (loc >= 0)
    {
        GLCall(glUniformMatrix3fv(loc, 1, GL_FALSE, &value[0][0]))
    }
}

int Shader::GetUniformLoc(const std::string& name)
{
    auto it = Uniforms.find(name);
    return it != Uniforms.end() ? it->second : -1;
}
