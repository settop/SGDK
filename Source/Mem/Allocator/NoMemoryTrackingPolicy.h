#pragma once

#include <Mem/AllocationParams.h>

struct NoMemoryTrackingPolicy
{
	inline void OnAllocation(void *_ptr, size_t _size, size_t _alignment, AllocationParams _allocationParams){}
	inline void OnDeallocation(void *_ptr){}
};