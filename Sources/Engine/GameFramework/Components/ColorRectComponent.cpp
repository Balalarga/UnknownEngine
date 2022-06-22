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
};

ColorRectComponent::ColorRectComponent(Actor& owner, Scene* scene, const glm::fvec4& color):
	Component(owner),
	_color(color),
	_rectData(GenerateRectData(color)),
	_rect(scene->AddObject(new IRenderable({DataPtr(_rectData), BufferLayout().Float(3).Float(4)})))
{
	
}


}
