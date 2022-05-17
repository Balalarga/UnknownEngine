#include "Window.h"
#include <iostream>

#include <imgui.h>
#include <imgui_impl_sdl.h>
#include <imgui_impl_opengl3.h>


AppWindow::AppWindow(const AppWindowParams& params):
    Params(params)
{
    SDLWindow = SDL_CreateWindow(Params.Title.c_str(),
            Params.X,
            Params.Y,
            Params.Width,
            Params.Height,
            Params.Flags);
    GlContext = SDL_GL_CreateContext(SDLWindow);

    SDL_GL_MakeCurrent(SDLWindow, GlContext);

    if (Params.Vsync)
        SDL_GL_SetSwapInterval(1);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();
    const char* glsl_version = "#version 130";

    ImGui_ImplSDL2_InitForOpenGL(SDLWindow, GlContext);
    ImGui_ImplOpenGL3_Init(glsl_version);
}

AppWindow::~AppWindow()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    SDL_GL_DeleteContext(GlContext);
    SDL_DestroyWindow(SDLWindow);
}

void AppWindow::SetBackgroundColor(const glm::vec4 newColor)
{
    BackColor = newColor;
    glClearColor(BackColor.r, BackColor.g, BackColor.b, BackColor.a);
}

void AppWindow::Show()
{
    bShouldClose = false;

    while (!bShouldClose)
    {
        HandleEvents();
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

void AppWindow::Close()
{
    bShouldClose = true;
}

void AppWindow::HandleEvents()
{
    auto& Input = InputSystem::Get();
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
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
}

void AppWindow::Clear()
{
    glClear(GL_COLOR_BUFFER_BIT);
}

void AppWindow::Render()
{

}

void AppWindow::PostRender()
{
    SDL_GL_SwapWindow(SDLWindow);
}

void AppWindow::ClearImGui()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();
}

void AppWindow::RenderImGui()
{
    
}

void AppWindow::PostRenderImGui()
{
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
