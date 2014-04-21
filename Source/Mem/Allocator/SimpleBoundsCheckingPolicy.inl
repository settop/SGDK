#pragma once

#include "SimpleBoundsCheckingPolicy.h"

#include <Core/Utils.h>

inline void SimpleBoundsCheckingPolicy::GuardFront
(
	void *_frontPtr
)
{
	*(uint32*)_frontPtr = FrontTag;
}

inline void SimpleBoundsCheckingPolicy::GuardBack
(
	void *_backPtr
)
{
	*(uint32*)_backPtr = BackTag;
}

inline void SimpleBoundsCheckingPolicy::CheckFront
(
	void *_frontPtr
)
{
	Verify(*(uint32*)_frontPtr == FrontTag, "Bounds checking front has failed, there has been a memory stomp!!");
}

inline void SimpleBoundsCheckingPolicy::CheckBack
(
	void *_backPtr
)
{
	Verify(*(uint32*)_backPtr == BackTag, "Bounds checking back has failed, there has been a memory stomp!!");
}