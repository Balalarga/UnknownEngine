#include <iostream>

#include "GameMock.h"
#include "Engine/Utils/Log.h"
#include "WindowSystem/OpenglWindow.h"

using namespace std;


int main(int argc, char** argv)
{
    Log::ScopedLog("App lifetime");
    
    ISdlWindowParams Params;
    Params.vsync = true;
    std::shared_ptr<OpenglWindow> Window = std::make_shared<OpenglWindow>(Params);


    GameMock Game(Window.get());
    Game.Init();
    Game.Run();
    
    return 0;
}
