#pragma once

#include <vector>

#include "OpenGL/Core/IRenderable.h"
#include "WindowSystem/ISdlWindow.h"


class OpenglWindow: public ISdlWindow
{
public:
    OpenglWindow(const ISdlWindowParams& params = ISdlWindowParams());
    ~OpenglWindow();

    IRenderable* AddObject(IRenderable*&& Obj);

    void SetBackgroundColor(const glm::vec4 newColor) override;
    void Render() override;
    
#if USE_IMGUI
    void ClearImGui() override;
    void PostRenderImGui() override;
#endif

private:
    std::vector<std::unique_ptr<IRenderable>> RenderObjects;
    SDL_GLContext GlContext;
};
