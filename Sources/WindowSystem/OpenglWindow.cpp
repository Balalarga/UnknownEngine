#include "OpenglWindow.h"

#if USE_IMGUI
    #include <imgui_impl_sdl.h>
    #include <imgui_impl_opengl3.h>
#endif


OpenglWindow::OpenglWindow(const ISdlWindowParams& params):
    ISdlWindow(params)
{
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

    GlContext = SDL_GL_CreateContext(GetSdlWindow());

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
        return;

    SDL_GL_MakeCurrent(GetSdlWindow(), GlContext);

#if USE_IMGUI
    const char* glsl_version = "#version 130";

    ImGui_ImplSDL2_InitForOpenGL(GetSdlWindow(), GlContext);
    ImGui_ImplOpenGL3_Init(glsl_version);
#endif
}

OpenglWindow::~OpenglWindow()
{
    SDL_GL_DeleteContext(GlContext);
#if USE_IMGUI
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
#endif
}

IRenderable* OpenglWindow::AddObject(IRenderable*&& Obj)
{
    RenderObjects.push_back(std::unique_ptr<IRenderable>(Obj));
    return RenderObjects.back().get();
}

void OpenglWindow::SetBackgroundColor(const glm::vec4 newColor)
{
    ISdlWindow::SetBackgroundColor(newColor);
    glClearColor(newColor.r, newColor.g, newColor.b, newColor.a);
}

void OpenglWindow::Render()
{
    for (auto& Obj: RenderObjects)
    {
        Obj->GetShader()->Bind();
        Obj->Render();
        Obj->GetShader()->Unbind();
    }
    ISdlWindow::Render();
}

#if USE_IMGUI
void OpenglWindow::ClearImGui()
{
    ImGui_ImplOpenGL3_NewFrame();
    ISdlWindow::ClearImGui();
}

void OpenglWindow::PostRenderImGui()
{
    ISdlWindow::PostRenderImGui();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
#endif
