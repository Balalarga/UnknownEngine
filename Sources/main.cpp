#include <iostream>
#include "WindowSystem/SdlSubsystem.h"

using namespace std;


int main(int argc, char** argv)
{
    SDLSubsystem& Sdl = SDLSubsystem::Get();
    Sdl.Init();
    AppWindowParams params("Window");
    params.Vsync = true;
    
    auto Window = Sdl.MakeWindow({"Window"});
    Window->SetBackgroundColor(glm::vec4(0.6, 0.6, 0.6, 1.0));
    
    Window->Show();

    return 0;
}
