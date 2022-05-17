#pragma once

#include <vector>

#include "OpenGL/Core/IRenderable.h"
#include "WindowSystem/AppWindow.h"



class OpenglWindow: public AppWindow
{
public:
    OpenglWindow(const AppWindowParams& params);

    template<class T, class... Args>
    IRenderable& AddObject(Args... args)
    {
        RenderObjects.push_back(std::make_unique<T>(args...));
        return *RenderObjects.back().get();
    }

    void Render() override;


private:
    std::vector<std::unique_ptr<IRenderable>> RenderObjects;
};
