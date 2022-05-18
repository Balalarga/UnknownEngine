#ifndef ISdlWindow_H
#define ISdlWindow_H

#include <string>

#include <GL/glew.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include <glm/glm.hpp>

#include "InputSystem.h"


struct ISdlWindowParams
{
    ISdlWindowParams(const std::string& title = "New Window"):
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


class ISdlWindow
{
public:
    ISdlWindow(const ISdlWindowParams& params = ISdlWindowParams());
    virtual ~ISdlWindow();

    void Show();
    void Close();

    inline const glm::vec4& GetBackgroundColor() { return BackColor; }
    virtual void SetBackgroundColor(const glm::vec4 newColor);
    
    virtual void HandleEvents(SDL_Event& event);
    virtual void Clear();
    virtual void Render() = 0;
    virtual void PostRender();

#if USE_IMGUI
    virtual void ClearImGui();
    virtual void RenderImGui();
    virtual void PostRenderImGui();
#endif

    inline SDL_Window* GetSdlWindow() const { return SDLWindow; }
    inline const ISdlWindowParams& GetParams() const { return Params; }


private:
    ISdlWindowParams Params;
    SDL_Window* SDLWindow;

    bool bShouldClose;
    glm::vec4 BackColor;
};


#endif //WINDOW_H
