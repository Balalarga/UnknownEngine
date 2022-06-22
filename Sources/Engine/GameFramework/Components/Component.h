#pragma once

namespace Unk
{


class Component
{
	friend class Actor;
public:
	Component(Actor& owner);
	virtual ~Component() = default;
	
	Actor& GetOwner() { return _owner; }
	
	void SetTicking(bool state) { _bTicking = state; }
	bool IsTicking() const { return _bTicking; }

	virtual void Tick(float deltaTime);


private:
	Actor& _owner;
	bool _bTicking = false;
};


}