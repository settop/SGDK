
#include "Mem.h"

bool Mem::s_initalised = false;
GlobalAllocatorType *Mem::s_allocator = nullptr;

void Mem::StaticInit
(
)
{
	s_allocator = new GlobalAllocatorType();
	s_initalised = true;
}

void Mem::StaticShutdown
(
)
{
	s_initalised = false;
	delete s_allocator;
}