#include "SdlSubsystem.h"

#include <SDL.h>
#include <SDL_opengl.h>


SDLSubsystem& SDLSubsystem::Get()
{
    static SDLSubsystem self;
    return self;
}

SDLSubsystem::~SDLSubsystem()
{
    for (auto& i: Windows)
        i.second.reset();
    SDL_Quit();
}

SDLError SDLSubsystem::Init()
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) != 0)
        return SDLError::Bad;

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

    return SDLError::Ok;
}

