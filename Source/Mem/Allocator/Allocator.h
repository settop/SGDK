#pragma once

#include "AllocatorDefs.h"
#include <Mem/AllocationParams.h>

template 
<
	typename AllocationPolicy,
	typename ThreadPolicy,
	typename BoundsCheckingPolicy,
	typename MemoryTrackingPolicy,
	typename MemoryTaggingPolicy
>
class Allocator
{
public:
	Allocator();
	Allocator(AllocationPolicy const &_allocationPolicy);

	void* Allocate(size_t _size, size_t _alignment, AllocationParams _allocationParams);
	void Free(void* _ptr);
private:

	struct Header
	{
		typename BoundsCheckingPolicy::FrontGuard m_guard;
		typename AllocationPolicy::HeaderData m_header;
	};
	struct Footer
	{
		typename BoundsCheckingPolicy::RearGuard m_guard;
	};

	AllocationPolicy m_allocator;
	ThreadPolicy m_threadGuard;
	BoundsCheckingPolicy m_boundsChecker;
	MemoryTrackingPolicy m_memoryTracker;
	MemoryTaggingPolicy m_memoryTagger;
};

#include "Allocator.inl"