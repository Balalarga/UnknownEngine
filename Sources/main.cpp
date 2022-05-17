#include <iostream>
#include "WindowSystem/OpenglWindow.h"
#include "WindowSystem/SdlSubsystem.h"

using namespace std;


void BaseInput(AppWindow* Window)
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
    struct Vertex{
        glm::vec3 pos;
        glm::vec4 color;
    };

    Vertex triangle[]{
        {{-1.f, -1.f, 0.f}, {1.f, 1.f, 1.f, 1.f}},
        {{-1.f,  1.f, 0.f}, {1.f, 1.f, 1.f, 1.f}},
        {{ 0.f,  0.f, 0.f}, {1.f, 1.f, 1.f, 1.f}},
        };
    Buffer buffer;
    buffer.Layout.Float(3).Float(4);
    buffer.Data = DataPtr(&triangle, 3, sizeof(Vertex));
    auto& Obj1 = Window->AddObject<IRenderable>(buffer);
}

int main(int argc, char** argv)
{
    SDLSubsystem& Sdl = SDLSubsystem::Get();
    Sdl.Init();
    AppWindowParams Params("Window");
    Params.Vsync = true;
    
    std::shared_ptr<OpenglWindow> Window = Sdl.MakeWindow<OpenglWindow>(Params);
    Window->SetBackgroundColor(glm::vec4(0.6, 0.6, 0.6, 1.0));
    
    BaseInput(Window.get());
    BaseObjects(Window.get());

    Window->Show();

    return 0;
}

