#pragma once

namespace Unk
{


class Component
{
	friend class Actor;
public:
	Component() = default;
	virtual ~Component() = default;
};


}