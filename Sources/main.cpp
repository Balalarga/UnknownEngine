#include <iostream>

#include "Engine/Resources/ShaderStorage.h"
#include "Engine/Utils/Log.h"
#include "OpenGL/Core/Scene.h"
#include "WindowSystem/OpenglWindow.h"
#include "Engine/Utils/Checks.h"

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


bool LoadShaders()
{
    auto& storage = ShaderStorage::Self();
    auto vsh = storage.LoadShaderPart("devault_vertex", ShaderPart::Type::Vertex, sDefaultVertexShader);
    CheckReturn(vsh, false);
    
    auto fsh = storage.LoadShaderPart("devault_fragment", ShaderPart::Type::Fragment, sDefaultFragmentShader);
    CheckReturn(fsh, false);

    auto shader = storage.LoadShader("default",{vsh, fsh});
    CheckReturn(shader, false);

    return true;
}


void BaseObjects(Scene& scene)
{
    struct Vertex
    {
        glm::fvec3 pos;
        glm::fvec4 color;
    };
    vector<Vertex> triangle
    {
        {glm::fvec3{-0.2f, -0.4f, 0.f}, glm::fvec4{1.f, 0.f, 0.f, 1.f}},
        {glm::fvec3{-0.2f,  0.4f, 0.f}, glm::fvec4{0.f, 1.f, 0.f, 1.f}},
        {glm::fvec3{ 0.3f,  0.0f, 0.f}, glm::fvec4{0.f, 0.f, 1.f, 1.f}},
    };
    Buffer buffer(DataPtr(triangle), BufferLayout().Float(3).Float(4));
    
    auto& Obj1 = scene.AddObject(new IRenderable(buffer));
    auto shader = ShaderStorage::Self().GetShader("default");
    CheckMsgReturn(!shader, "Shader not compiled");
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

    CheckReturn(LoadShaders(), -1);
    
    BaseInput(Window.get());

    Scene scene;
    BaseObjects(scene);
    Window->SetScene(&scene);
    
    Window->Show();
    
    ShaderStorage::Destroy();
    
    return 0;
}
