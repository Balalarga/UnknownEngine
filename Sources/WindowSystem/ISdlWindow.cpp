#include "ISdlWindow.h"
#include <iostream>

#include <imgui.h>
#include <imgui_impl_sdl.h>


static Uint32 DefaultSdlSubsystems = SDL_INIT_EVERYTHING;

ISdlWindow::ISdlWindow(const ISdlWindowParams& params):
    Params(params)
{
    if (SDL_Init(DefaultSdlSubsystems) != 0)
        return;

    SDLWindow = SDL_CreateWindow(Params.Title.c_str(),
            Params.X,
            Params.Y,
            Params.Width,
            Params.Height,
            Params.Flags);
    
    if (Params.Vsync)
        SDL_GL_SetSwapInterval(1);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();
}

ISdlWindow::~ISdlWindow()
{
    ImGui::DestroyContext();
    SDL_DestroyWindow(SDLWindow);
}

void ISdlWindow::SetBackgroundColor(const glm::vec4 newColor)
{
    BackColor = newColor;
}

void ISdlWindow::Show()
{
    bShouldClose = false;

    while (!bShouldClose)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
            HandleEvents(event);

        if (bShouldClose)
            break;

        ClearImGui();
        RenderImGui();
        PostRenderImGui();

        Clear();
        Render();
        PostRender();
    }
}

void ISdlWindow::Close()
{
    bShouldClose = true;
}

void ISdlWindow::HandleEvents(SDL_Event& event)
{
    auto& Input = InputSystem::Get();
    ImGui_ImplSDL2_ProcessEvent(&event);
    switch(event.type)
    {
        case SDL_QUIT:
            bShouldClose = true;
            break;
        case SDL_WINDOWEVENT:
            bShouldClose = event.window.event == SDL_WINDOWEVENT_CLOSE &&
                event.window.windowID == SDL_GetWindowID(SDLWindow);
            break;
        case SDL_KEYDOWN:
            Input.OnStateChange(event.key.keysym.scancode,
                    event.key.repeat == 0 ? KeyState::Pressed : KeyState::Repeated);
            break;
        case SDL_KEYUP:
            Input.OnStateChange(event.key.keysym.scancode, KeyState::Released);
            break;
    }
}

void ISdlWindow::Clear()
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
}

void ISdlWindow::Render()
{

}

void ISdlWindow::PostRender()
{
    SDL_GL_SwapWindow(SDLWindow);
}

void ISdlWindow::ClearImGui()
{
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();
}

void ISdlWindow::RenderImGui()
{
    
}

void ISdlWindow::PostRenderImGui()
{
    ImGui::Render();
}
