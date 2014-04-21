#pragma once

#include <malloc.h>

class GlobalAllocationPolicy
{
public:
	void* Allocate(size_t _size, size_t _alignment, size_t _alignmentOffset);
	void Free(void* _ptr);
	size_t GetAllocationSize(void* _ptr);
private:
};

#include "GlobalAllocationPolicy.inl"