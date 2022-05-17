#include <iostream>
#include "WindowSystem/SdlSubsystem.h"

using namespace std;


void BaseInput(AppWindow* Window)
{
    InputSystem::Get().Add(SDL_SCANCODE_SPACE, [](KeyState state){
            if (state == KeyState::Pressed)
                std::cout << "Space pressed\n";
            else if (state == KeyState::Released)
                std::cout << "Space released\n";
        });
    InputSystem::Get().Add(SDL_SCANCODE_ESCAPE, [&Window](KeyState state){
            if (state == KeyState::Pressed)
                Window->Close();
        });
}


int main(int argc, char** argv)
{
    SDLSubsystem& Sdl = SDLSubsystem::Get();
    Sdl.Init();
    AppWindowParams Params("Window");
    Params.Vsync = true;
    
    std::shared_ptr<AppWindow> Window = Sdl.MakeWindow(Params);
    Window->SetBackgroundColor(glm::vec4(0.6, 0.6, 0.6, 1.0));
    
    BaseInput(Window.get());

    Window->Show();

    return 0;
}

