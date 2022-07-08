#pragma once
#include <vector>


struct DataPtr
{
	DataPtr();
	DataPtr(void* ptr, unsigned count, unsigned itemSize);
    
	template<class T>
	DataPtr(const std::vector<T>& items):
		DataPtr((void*)&items[0], items.size(), sizeof(T))
	{}

	void* Ptr;
	unsigned Count;
	unsigned ItemSize;
};


inline DataPtr::DataPtr():
	Ptr(nullptr),
	Count(0),
	ItemSize(0)
{
}

inline DataPtr::DataPtr(void* ptr, unsigned count, unsigned itemSize):
	Ptr(ptr),
	Count(count),
	ItemSize(itemSize)
{
}
