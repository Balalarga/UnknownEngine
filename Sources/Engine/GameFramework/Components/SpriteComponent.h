#pragma once

#include "Component.h"

class IRenderable;

namespace Unk
{


class SpriteComponent: public Component
{
public:
	SpriteComponent();
	

private:
	IRenderable* _renderable;
};


}
