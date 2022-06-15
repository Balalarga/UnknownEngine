#include <iostream>

#include "GameMock.h"
#include "Engine/Utils/Log.h"
#include "WindowSystem/OpenglWindow.h"

#include "Engine/GameFramework/Objects/Actor.h"

using namespace std;


int main(int argc, char** argv)
{
    Log::ScopedLog("App lifetime");
    
    ISdlWindowParams params;
    params.vsync = true;
    std::shared_ptr<OpenglWindow> Window = std::make_shared<OpenglWindow>(params);

    GameMock game(Window.get());
    game.Init();
    game.Run();

    Unk::Actor obj;
    Unk::Component& component = obj.Add<Unk::Component>();

    return 0;
}
