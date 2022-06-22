#pragma once
#include <glm/glm.hpp>

#include "Component.h"
#include "OpenGL/Core/IRenderable.h"


class Scene;

namespace Unk
{


class ColorRectComponent: public Component
{
public:
	ColorRectComponent(Actor& owner, Scene* scene, const glm::fvec4& color = glm::fvec4(1));
	
	IRenderable& GetRenderable() { return _rect; }
	
	
private:
	glm::fvec4 _color;
	std::vector<float> _rectData;
	IRenderable& _rect;
};


}
