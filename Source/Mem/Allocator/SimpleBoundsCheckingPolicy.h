#pragma once

#include <Core/TypeDefs.h>

struct SimpleBoundsCheckingPolicy
{
	static uint32 const FrontTag = 0xdededede;
	static uint32 const BackTag = 0xefefefef;

	static uint32 const SIZE_FRONT = sizeof(FrontTag);
	static uint32 const SIZE_BACK = sizeof(BackTag);

	inline void GuardFront(void *_frontPtr);
	inline void GuardBack(void *_backPtr);

	inline void CheckFront(void *_frontPtr);
	inline void CheckBack(void *_backPtr);

};

#include "SimpleBoundsCheckingPolicy.inl"