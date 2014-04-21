#pragma once

#include "GlobalAllocationPolicy.h"

void* GlobalAllocationPolicy::Allocate
(
	size_t _size,
	size_t _alignment,
	size_t _alignmentOffset
)
{
	return _aligned_offset_malloc(_size, _alignment, _alignmentOffset);
}

void GlobalAllocationPolicy::Free
(
	void* _ptr
)
{
	_aligned_free(_ptr);
}

size_t GlobalAllocationPolicy::GetAllocationSize
(
	void* _ptr
)
{
	return _msize(_ptr);
}