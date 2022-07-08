#include "Component.h"

namespace Unk
{


Component::Component(Actor& owner)
{
	RegisterAt(owner);
}

void Component::Tick(float deltaTime)
{
}

void Component::RegisterAt(Actor& actor)
{
	_owner = &actor;
}


}
