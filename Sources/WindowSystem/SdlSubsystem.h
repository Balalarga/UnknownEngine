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
    
    template<class T>
    std::shared_ptr<T> MakeWindow(AppWindowParams params)
    {
        auto founded = Windows.find(params.Title);
        if (founded != Windows.end())
            return std::dynamic_pointer_cast<T>(founded->second);

        Windows[params.Title] = std::make_shared<T>(params);
        return std::static_pointer_cast<T>(Windows[params.Title]);
    }
    
    SDLError Init();
    
    
protected:
    SDLSubsystem() = default;
    ~SDLSubsystem();
    std::map<std::string, std::shared_ptr<AppWindow>> Windows;
};


#endif //SDLSUBSYSTEM_H
