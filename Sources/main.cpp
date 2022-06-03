#include <iostream>

#include "Engine/Utils/Log.h"
#include "OpenGL/Core/Scene.h"
#include "WindowSystem/OpenglWindow.h"

using namespace std;


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
    Window->SetScene(&scene);
    
    Window->Show();
    
    return 0;
}
