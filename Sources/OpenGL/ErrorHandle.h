#pragma once

#include <GL/glew.h>
#include <iostream>

/* Error handling */
#define DEBUG_ASSERT(x) if(!(x)) __debugbreak();

/* Use GLCall wrapper for handling opengl function errors */
#define GLCall(x) GLClearError(); \
    x;\
    DEBUG_ASSERT(GLLogCall(#x, __FILE__, __LINE__))

void GLClearError()
{
    while(glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* func, const char* file, int line)
{
    while(GLenum error = glGetError())
    {
        std::cout<<"[OpenglError] "<<line<<": "<<file<<" "<<func<<" - ";
        std::cout <<" (0x"<<std::hex<<error<<")\n";
        return false;
    }
    return true;
}

