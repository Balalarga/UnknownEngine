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
	ColorRectComponent(Scene* scene);
	
	IRenderable& GetRenderable() { return _rect; }
	
	void SetColor(const glm::fvec4& newColor);
	glm::fvec4 GetColor() const { return _color; }

	
private:
	glm::fvec4 _color = glm::fvec4(1);
	std::vector<float> _rectData;
	IRenderable& _rect;
};


}
