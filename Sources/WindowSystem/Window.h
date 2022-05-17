#ifndef WINDOW_H
#define WINDOW_H

#include <string>

#include <GL/glew.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include <glm/glm.hpp>

#include "InputSystem.h"


struct AppWindowParams
{
    AppWindowParams(const std::string& title):
        Title(title)
    {}
    std::string Title;
    unsigned X = SDL_WINDOWPOS_CENTERED;
    unsigned Y = SDL_WINDOWPOS_CENTERED;
    unsigned Width = 800;
    unsigned Height = 600;
    unsigned Flags = SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI;

    bool Vsync = false;
};


class AppWindow
{
public:
    AppWindow(const AppWindowParams& params);
    ~AppWindow();

    void SetBackgroundColor(const glm::vec4 newColor);
    inline const glm::vec4& GetBackgroundColor() { return BackColor; }
    
    void Show();
    void Close();
    
    void HandleEvents();
    void Clear();
    void Render();
    void PostRender();
    
    void ClearImGui();
    void RenderImGui();
    void PostRenderImGui();
    

private:
    AppWindowParams Params;
    SDL_Window* SDLWindow;
    SDL_GLContext GlContext;
    bool bShouldClose;
    
    glm::vec4 BackColor;
};


#endif //WINDOW_H
