#ifndef PLATE_SDLSUBSYSTEM_H
#define PLATE_SDLSUBSYSTEM_H

#include <map>
#include <memory>

#include "Window.h"


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


#endif //PLATE_SDLSUBSYSTEM_H
