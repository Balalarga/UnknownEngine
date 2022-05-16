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

void AppWindow::Hide()
{
    bShouldClose = false;
}

void AppWindow::HandleEvents()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        ImGui_ImplSDL2_ProcessEvent(&event);
        if (event.type == SDL_QUIT)
        {
            bShouldClose = true;
        }
        if (event.type == SDL_WINDOWEVENT &&
                event.window.event == SDL_WINDOWEVENT_CLOSE &&
                event.window.windowID == SDL_GetWindowID(SDLWindow))
        {
            bShouldClose = true;
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
