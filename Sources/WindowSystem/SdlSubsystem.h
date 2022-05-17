#ifndef SDLSUBSYSTEM_H
#define SDLSUBSYSTEM_H

#include <map>
#include <memory>

#include "AppWindow.h"


enum class SDLError
{
    Ok,
    Bad
};

struct SDLInitParams
{
    
};


class SDLSubsystem
{
public:
    static SDLSubsystem& Get();
    
    std::shared_ptr<AppWindow> MakeWindow(AppWindowParams params);
    
    SDLError Init();
    
    
protected:
    SDLSubsystem() = default;
    ~SDLSubsystem();
    std::map<std::string, std::shared_ptr<AppWindow>> Windows;
};


#endif //SDLSUBSYSTEM_H
