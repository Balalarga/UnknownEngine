#pragma once

namespace Unk
{


class Component
{
	friend class Actor;
	void RegisterAt(Actor& actor);
	
public:
	Component() = default;
	Component(Actor& owner);
	virtual ~Component() = default;
	
	Actor* GetOwner() { return _owner; }
	bool IsOwned() const { return _owner != nullptr; }
	
	void SetTicking(bool state) { _bTicking = state; }
	bool IsTicking() const { return _bTicking; }

	virtual void Tick(float deltaTime);


private:
	Actor* _owner = nullptr;
	bool _bTicking = false;
};


}