#pragma once
#include "OpenGL/Core/IRenderable.h"


class Rectangle: public IRenderable
{
public:
	Rectangle(const glm::fvec3& pos, const glm::fvec2& size);

	
private:	
	Buffer _buffer;	
};
