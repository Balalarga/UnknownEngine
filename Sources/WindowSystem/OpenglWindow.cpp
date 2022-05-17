#include "OpenglWindow.h"


OpenglWindow::OpenglWindow(const AppWindowParams& params):
    AppWindow(params)
{

}

void OpenglWindow::Render()
{
    for (auto& Obj: RenderObjects)
    {
        Obj->GetShader()->Bind();
        Obj->Render();
        Obj->GetShader()->Unbind();
    }
    AppWindow::Render();
}
