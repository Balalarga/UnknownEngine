#version 330

layout(location = 0) in vec3 iVert;
layout(location = 1) in vec4 iVertColor;

uniform mat4 uModelMatrix = mat4(1);

out vec4 vertColor;

void main()
{
    gl_Position = uModelMatrix * vec4(iVert, 1.0);
    vertColor = iVertColor;
}