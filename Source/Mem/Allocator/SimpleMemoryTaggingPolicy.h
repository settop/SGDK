#pragma once

#include <Core/TypeDefs.h>

struct SimpleMemoryTaggingPolicy
{
	static uint8 const AllocTag[4];
	static uint8 const DeallocTag[4];

	void TagAllocation(void *_ptr, size_t _size);
	void TagDeallocation(void *_ptr, size_t _size);
};

#include "SimpleMemoryTaggingPolicy.inl"