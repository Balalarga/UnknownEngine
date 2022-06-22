#include "Component.h"

namespace Unk
{


Component::Component(Actor& owner):
	_owner(owner)
{
}

void Component::Tick(float deltaTime)
{
}


}
