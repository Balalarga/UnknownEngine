#pragma once
#include <map>
#include <memory>

#include "Engine/GameFramework/Components/Component.h"


namespace Unk
{


class Actor
{
public:
	Actor() = default;
	virtual ~Actor();
	
	template<class T, class ...TArgs>
	T* Add(TArgs&&... args)
	{
		T* comp = new T(std::forward(*this, args)...);
		_components.emplace(std::make_pair(&typeid(T), comp));
		return comp;
	}

	template<class T>
	T* GetComponent();

	template<class T>
	inline bool HasComponent() const;


private:
    std::map<type_info*, std::unique_ptr<Component>> _components;
};


template <class T>
T* Actor::GetComponent()
{
	auto it = _components.find(&typeid(T));
	if (it == _components.end())
		return nullptr;
	return *it->second;
}

template <class T>
inline bool Actor::HasComponent() const
{
	return GetComponent<T>() != nullptr;
}


}
