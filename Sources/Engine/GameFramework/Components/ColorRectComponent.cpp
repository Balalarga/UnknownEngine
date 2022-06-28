#include "ColorRectComponent.h"

#include "OpenGL/Core/Scene.h"

namespace Unk
{


static std::vector<float> GenerateRectData(const glm::fvec4& color)
{
	return{
		-1.f, -1.f, 0.f, color.r, color.g, color.b, color.a,
		-1.f,  1.f, 0.f, color.r, color.g, color.b, color.a,
		 1.f,  1.f, 0.f, color.r, color.g, color.b, color.a,
		 1.f,  1.f, 0.f, color.r, color.g, color.b, color.a,
		 1.f, -1.f, 0.f, color.r, color.g, color.b, color.a,
		-1.f, -1.f, 0.f, color.r, color.g, color.b, color.a,
	};
}

ColorRectComponent::ColorRectComponent(Scene* scene):
	_rectData(GenerateRectData(_color)),
	_rect(scene->AddObject(new IRenderable({DataPtr(_rectData), BufferLayout().Float(3).Float(4)})))
{
	
}

void ColorRectComponent::SetColor(const glm::fvec4& newColor)
{
	_color = newColor;
	_rectData = GenerateRectData(_color);
	_rect.Setup({DataPtr(_rectData), BufferLayout().Float(3).Float(4)});
}


}
