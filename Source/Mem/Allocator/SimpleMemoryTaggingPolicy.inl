#pragma once

#include "SimpleMemoryTaggingPolicy.h"

uint8 const SimpleMemoryTaggingPolicy::AllocTag[4] = {0xba, 0xad, 0xf0, 0x0d};
uint8 const SimpleMemoryTaggingPolicy::DeallocTag[4] = { 0xde, 0xad, 0xbe, 0xef };

void SimpleMemoryTaggingPolicy::TagAllocation
(
	void *_ptr,
	size_t _size
)
{
	uint32 tagIndex = 0u;
	uint8 *tagPtr = (uint8*)_ptr;
	while (_size > 0)
	{
		*tagPtr = AllocTag[tagIndex];
		tagIndex = (tagIndex + 1) % 4;
		--_size;
		++tagPtr;
	}
}

void SimpleMemoryTaggingPolicy::TagDeallocation
(
	void *_ptr, 
	size_t _size
)
{
	uint32 tagIndex = 0u;
	uint8 *tagPtr = (uint8*)_ptr;
	while (_size > 0)
	{
		*tagPtr = DeallocTag[tagIndex];
		tagIndex = (tagIndex + 1) % 4;
		--_size;
		++tagPtr;
	}
}