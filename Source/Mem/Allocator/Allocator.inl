#pragma once

#define AllocatorTemplateParams AllocationPolicy, ThreadPolicy, BoundsCheckingPolicy, MemoryTrackingPolicy, MemoryTaggingPolicy

template<typename AllocationPolicy, typename ThreadPolicy, typename BoundsCheckingPolicy, typename MemoryTrackingPolicy, typename MemoryTaggingPolicy>
Allocator<AllocatorTemplateParams>::Allocator
(
)
{
}

template<typename AllocationPolicy, typename ThreadPolicy, typename BoundsCheckingPolicy, typename MemoryTrackingPolicy, typename MemoryTaggingPolicy>
Allocator<AllocatorTemplateParams>::Allocator
(
	AllocationPolicy const &_allocationPolicy
) : m_allocator(_allocationPolicy)
{
}

template<typename AllocationPolicy,typename ThreadPolicy,typename BoundsCheckingPolicy,typename MemoryTrackingPolicy,typename MemoryTaggingPolicy>
void* Allocator<AllocatorTemplateParams>::Allocate
(
	size_t _size,
	size_t _alignment, 
	size_t _alignmentOffset,
	AllocationParams _allocationParams
)
{
	m_threadGuard.Enter();

	const size_t originalSize = size;
	const size_t newSize = size + BoundsCheckingPolicy::SIZE_FRONT + BoundsCheckingPolicy::SIZE_BACK;

	char* plainMemory = static_cast<char*>(m_allocator.Allocate(newSize, alignment, _alignmentOffset + BoundsCheckingPolicy::SIZE_FRONT));

	m_boundsChecker.GuardFront(plainMemory);
	m_memoryTagger.TagAllocation(plainMemory + BoundsCheckingPolicy::SIZE_FRONT, originalSize);
	m_boundsChecker.GuardBack(plainMemory + BoundsCheckingPolicy::SIZE_FRONT + originalSize);

	m_memoryTracker.OnAllocation(plainMemory, newSize, alignment, _allocationParams);
	m_threadGuard.Leave();

	return (plainMemory + BoundsCheckingPolicy::SIZE_FRONT);
}

template<typename AllocationPolicy, typename ThreadPolicy, typename BoundsCheckingPolicy, typename MemoryTrackingPolicy, typename MemoryTaggingPolicy>
void Allocator<AllocatorTemplateParams>::Free
(
	void* _ptr
)
{
	m_threadGuard.Enter();

	char* originalMemory = static_cast<char*>(ptr)-BoundsCheckingPolicy::SIZE_FRONT;
	const size_t allocationSize = m_allocator.GetAllocationSize(originalMemory);

	m_boundsChecker.CheckFront(originalMemory);
	m_boundsChecker.CheckBack(originalMemory + BoundsCheckingPolicy::SIZE_FRONT + allocationSize);

	m_memoryTracker.OnDeallocation(originalMemory);

	m_memoryTagger.TagDeallocation(originalMemory, allocationSize);

	m_allocator.Free(originalMemory);

	m_threadGuard.Leave();
}

#undef AllocatorTemplaeParams