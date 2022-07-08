﻿#include "ISdlWindow.h"
#include <iostream>

#include <GL/glew.h>

#if USE_IMGUI
    #include <imgui.h>
    #include <imgui_impl_sdl.h>
#endif


static Uint32 DefaultSdlSubsystems = SDL_INIT_EVERYTHING;

ISdlWindow::ISdlWindow(const ISdlWindowParams& params):
    _params(params),
    _scene(nullptr),
    _bShouldClose(false),
    _backColor(glm::vec4(0.15, 0.15, 0.15, 1.0))
{
    if (SDL_Init(DefaultSdlSubsystems) != 0)
        return;

    if (_params.fullScreen)
    {
        SDL_DisplayMode dm;

        if (SDL_GetDesktopDisplayMode(0, &dm) == 0)
        {
            _params.width = dm.w;
            _params.height = dm.h;
            _params.flags |= SDL_WINDOW_FULLSCREEN;
        }
        else
        {
            SDL_Log("SDL_GetDesktopDisplayMode failed: %s", SDL_GetError());
        }
    }
    
    _sdlWindow = SDL_CreateWindow(_params.title.c_str(),
        static_cast<int>(_params.x),
        static_cast<int>(_params.y),
        static_cast<int>(_params.width),
        static_cast<int>(_params.height),
        _params.flags);
    
    ISdlWindow::SetVSync(_params.vsync);

#if USE_IMGUI
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();
#endif
}

ISdlWindow::~ISdlWindow()
{
#if USE_IMGUI
    ImGui::DestroyContext();
#endif
    SDL_DestroyWindow(_sdlWindow);
    SDL_Quit();
}

void ISdlWindow::SetBackgroundColor(const glm::vec4& newColor)
{
    _backColor = newColor;
}

void ISdlWindow::PollEvents()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
        HandleEvents(event);
}

void ISdlWindow::RenderFrame()
{
#if USE_IMGUI
    ClearImGui();
    RenderImGui();
    PostRenderImGui();
#endif

    Clear();
    Render();
    PostRender();
}

void ISdlWindow::Show()
{
    _bShouldClose = false;
}

void ISdlWindow::Close()
{
    _bShouldClose = true;
}

void ISdlWindow::HandleEvents(SDL_Event& event)
{
    auto& Input = InputSystem::Get();
#if USE_IMGUI
    ImGui_ImplSDL2_ProcessEvent(&event);
#endif
    switch(event.type)
    {
        case SDL_QUIT:
            _bShouldClose = true;
            break;
        case SDL_WINDOWEVENT:
            if (event.window.event == SDL_WINDOWEVENT_CLOSE && event.window.windowID == SDL_GetWindowID(_sdlWindow))
                _bShouldClose = true;
            break;
        case SDL_KEYDOWN:
            Input.OnStateChange(event.key.keysym.scancode,
                event.key.repeat == 0 ? KeyState::Pressed : KeyState::Repeated);
            break;
        case SDL_KEYUP:
            Input.OnStateChange(event.key.keysym.scancode, KeyState::Released);
            break;
        default:
            break;
    }
}

void ISdlWindow::Clear()
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
}

void ISdlWindow::PostRender()
{
    SDL_GL_SwapWindow(_sdlWindow);
}

void ISdlWindow::SetVSync(bool enabled)
{
    _params.vsync = enabled;
}

#if USE_IMGUI
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
#endif