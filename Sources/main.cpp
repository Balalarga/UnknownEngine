#include <iostream>
#include "WindowSystem/OpenglWindow.h"

using namespace std;


std::string vshader = R"(
#version 330

layout(location = 0)in vec3 iVert;
layout(location = 1)in vec4 iVertColor;

out vec4 vertColor;

void main()
{
    gl_Position = vec4(iVert, 1.0);
    vertColor = iVertColor;
}
)";
std::string fshader = R"(
#version 330

in vec4 vertColor;
out vec4 fragColor;

void main()
{
    fragColor = vec4(0.5, 0.1, 0.1, 1.0);
    fragColor = vertColor;
}
)";


void BaseInput(ISdlWindow* Window)
{
    InputSystem::Get().Add(SDL_SCANCODE_ESCAPE,
        [&Window](KeyState state)
        {
            if (state == KeyState::Pressed)
                Window->Close();
        });
}

void BaseObjects(OpenglWindow* Window)
{
    struct {
        float x, y, z;
        float r, g, b, a;
    } triangle[] {
        {-0.1f, -0.1f, 0.f, 1.f, 0.f, 0.f, 1.f},
        {-0.1f,  0.1f, 0.f, 1.f, 1.f, 0.f, 1.f},
        { 0.0f,  0.0f, 0.f, 1.f, 0.f, 0.f, 1.f},
    };
    Buffer buffer(DataPtr(triangle, sizeof(triangle)/sizeof(triangle[0]), sizeof(triangle[0])), BufferLayout().Float(3).Float(4));
    auto* Obj1 = Window->AddObject(new IRenderable(buffer));
    Obj1->SetShader(std::make_shared<Shader>(vshader, fshader));
}

int main(int argc, char** argv)
{
    ISdlWindowParams Params;
    Params.Vsync = true;
    
    std::shared_ptr<OpenglWindow> Window = std::make_shared<OpenglWindow>(Params);
    Window->SetBackgroundColor(glm::vec4(0.6, 0.6, 0.6, 1.0));
    
    BaseInput(Window.get());
    BaseObjects(Window.get());

    Window->Show();

    return 0;
}

