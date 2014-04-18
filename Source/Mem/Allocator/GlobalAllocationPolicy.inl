#pragma once

#include "GlobalAllocationPolicy.h"

void* GlobalAllocationPolicy::Allocate
(
	size_t _size,
	size_t _alignement,
	size_t _alignmentOffset
)
{

}

void GlobalAllocationPolicy::Free
(
	void* _ptr
)
{
	free(_ptr);
}

size_t GlobalAllocationPolicy::GetAllocationSize
(
	void* _ptr
)
{
	return _msize(_ptr);
}