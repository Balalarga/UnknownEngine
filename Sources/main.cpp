#include <iostream>

#include "Engine/Utils/Log.h"
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
    Params.Vsync = true;
    std::shared_ptr<OpenglWindow> Window = std::make_shared<OpenglWindow>(Params);
    Window->SetBackgroundColor(glm::vec4(0.6, 0.6, 0.6, 1.0));
    
    BaseInput(Window.get());
    
    Window->Show();
    
    return 0;
}
