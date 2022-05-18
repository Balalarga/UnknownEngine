#pragma once

#include <vector>

#include "OpenGL/Core/IRenderable.h"
#include "WindowSystem/AppWindow.h"



class OpenglWindow: public AppWindow
{
public:
    OpenglWindow(const AppWindowParams& params);

    IRenderable* AddObject(IRenderable*&& Obj)
    {
        RenderObjects.push_back(std::unique_ptr<IRenderable>(Obj));
        return RenderObjects.back().get();
    }

    void Render() override;


private:
    std::vector<std::unique_ptr<IRenderable>> RenderObjects;
};
