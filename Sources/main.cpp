#include <iostream>

#include "Engine/Utils/Log.h"
#include "OpenGL/Core/Scene.h"
#include "WindowSystem/OpenglWindow.h"

using namespace std;

const std::string sDefaultVertexShader = R"(#version 330

layout(location = 0)in vec3 iVert;
layout(location = 1)in vec4 iVertColor;

out vec4 vertColor;

void main()
{
    gl_Position = vec4(iVert, 1.0);
    vertColor = iVertColor;
})";
const std::string sDefaultFragmentShader = R"(#version 330

in vec4 vertColor;

out vec4 fragColor;

void main()
{
    fragColor = vertColor;
})";


void BaseObjects(Scene& scene)
{
    DEFINE_LAYOUT(TriangleLayout)
        LAYOUT_FIELD(pos, glm::fvec3)
        LAYOUT_ARRAY(color, glm::fvec4)
    FINISH_LAYOUT()
    
    vector<> triangle
    {
        {glm::fvec3{-0.2f, -0.4f, 0.f}, glm::fvec4{1.f, 0.f, 0.f, 1.f}},
        {glm::fvec3{-0.2f,  0.4f, 0.f}, glm::fvec4{0.f, 1.f, 0.f, 1.f}},
        {glm::fvec3{ 0.3f,  0.0f, 0.f}, glm::fvec4{0.f, 0.f, 1.f, 1.f}},
    };
    Buffer buffer(DataPtr(triangle), BufferLayout().Float(3).Float(4));
    
    auto& Obj1 = scene.AddObject(new IRenderable(buffer));
    std::shared_ptr<Shader> shader(new Shader);
    shader->Setup({
        std::make_shared<ShaderPart>(ShaderPart::Type::Vertex, sDefaultVertexShader),
        std::make_shared<ShaderPart>(ShaderPart::Type::Fragment, sDefaultFragmentShader),
    });
    
    if (!shader->Compile(true))
    {
        Log::Error("Shader compilation error");
        return;
    }
    
    Obj1.SetShader(shader);
}


void BaseInput(ISdlWindow* Window)
{
    InputSystem::Get().Add(SDL_SCANCODE_ESCAPE,
        [&Window](KeyState state)
        {
            if (state == KeyState::Pressed)
                Window->Close();
        });
}


int main(int argc, char** argv)
{
    Log::ScopedLog("App lifetime");
    
    ISdlWindowParams Params;
    Params.vsync = true;
    std::shared_ptr<OpenglWindow> Window = std::make_shared<OpenglWindow>(Params);
    
    BaseInput(Window.get());

    Scene scene;
    BaseObjects(scene);
    Window->SetScene(&scene);
    
    Window->Show();
    
    return 0;
}
