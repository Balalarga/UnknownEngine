#pragma once
#include <map>
#include <memory>

#include "Engine/GameFramework/Components/Component.h"


namespace Unk
{


class Actor
{
public:
	virtual ~Actor();
	
	template<class T, class ...TArgs>
	T& Add(TArgs&& ...args);

	template<class T>
	T* GetComponent();

	template<class T>
	bool HasComponent() const;


private:
    std::map<const type_info*, std::unique_ptr<Component>> _components;
};



template <class T, class ... TArgs>
T& Actor::Add(TArgs&&... args)
{
	T& component = *_components.emplace(&typeid(T), std::make_unique<T>(args...)).first->second; 
	return component;
}

template <class T>
T* Actor::GetComponent()
{
	auto it = _components.find(&typeid(T));
	if (it == _components.end())
		return nullptr;
	return *it->second;
}

template <class T>
bool Actor::HasComponent() const
{
	return GetComponent<T>() != nullptr;
}

}
