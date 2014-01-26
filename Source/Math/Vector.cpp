#include "Vector.h"
#include <Core\TypeDefs.h>

namespace VectorMasks
{
	static uint32 PositiveMaskRaw[4] = { 0x7fffffff, 0x7fffffff, 0x7fffffff, 0x7fffffff };
	
	__m128 PositiveMask = _mm_load_ps( (float*)PositiveMaskRaw );

	static uint32 XMaskRaw[4] = { 0xffffffff, 0x00000000, 0x00000000, 0x00000000 };
	static uint32 YMaskRaw[4] = { 0x00000000, 0xffffffff, 0x00000000, 0x00000000 };
	static uint32 ZMaskRaw[4] = { 0x00000000, 0x00000000, 0xffffffff, 0x00000000 };
	static uint32 WMaskRaw[4] = { 0x00000000, 0x00000000, 0x00000000, 0xffffffff };

	__m128 XMask = _mm_load_ps( (float*)XMaskRaw );
	__m128 YMask = _mm_load_ps( (float*)YMaskRaw );
	__m128 ZMask = _mm_load_ps( (float*)ZMaskRaw );
	__m128 WMask = _mm_load_ps( (float*)WMaskRaw );

	static uint32 XYMaskRaw[4] = { 0xffffffff, 0xffffffff, 0x00000000, 0x00000000 };
	static uint32 XZMaskRaw[4] = { 0xffffffff, 0x00000000, 0xffffffff, 0x00000000 };
	static uint32 XWMaskRaw[4] = { 0xffffffff, 0x00000000, 0x00000000, 0xffffffff };
	static uint32 YZMaskRaw[4] = { 0x00000000, 0xffffffff, 0xffffffff, 0x00000000 };
	static uint32 YWMaskRaw[4] = { 0x00000000, 0xffffffff, 0x00000000, 0xffffffff };
	static uint32 ZWMaskRaw[4] = { 0x00000000, 0x00000000, 0xffffffff, 0xffffffff };

	__m128 XYMask = _mm_load_ps( (float*)XYMaskRaw );
	__m128 XZMask = _mm_load_ps( (float*)XZMaskRaw );
	__m128 XWMask = _mm_load_ps( (float*)XWMaskRaw );
	__m128 YZMask = _mm_load_ps( (float*)YZMaskRaw );
	__m128 YWMask = _mm_load_ps( (float*)YWMaskRaw );
	__m128 ZWMask = _mm_load_ps( (float*)ZWMaskRaw );



	static uint32 XInvMaskRaw[4] = { 0x00000000, 0xffffffff, 0xffffffff, 0xffffffff };
	static uint32 YInvMaskRaw[4] = { 0xffffffff, 0x00000000, 0xffffffff, 0xffffffff };
	static uint32 ZInvMaskRaw[4] = { 0xffffffff, 0xffffffff, 0x00000000, 0xffffffff };
	static uint32 WInvMaskRaw[4] = { 0xffffffff, 0xffffffff, 0xffffffff, 0x00000000 };

	__m128 XInvMask = _mm_load_ps( (float*)XInvMaskRaw );
	__m128 YInvMask = _mm_load_ps( (float*)YInvMaskRaw );
	__m128 ZInvMask = _mm_load_ps( (float*)ZInvMaskRaw );
	__m128 WInvMask = _mm_load_ps( (float*)WInvMaskRaw );

	static uint32 XYInvMaskRaw[4] = { 0x00000000, 0x00000000, 0xffffffff, 0xffffffff };
	static uint32 XZInvMaskRaw[4] = { 0x00000000, 0xffffffff, 0x00000000, 0xffffffff };
	static uint32 XWInvMaskRaw[4] = { 0x00000000, 0xffffffff, 0xffffffff, 0x00000000 };
	static uint32 YZInvMaskRaw[4] = { 0xffffffff, 0x00000000, 0x00000000, 0xffffffff };
	static uint32 YWInvMaskRaw[4] = { 0xffffffff, 0x00000000, 0xffffffff, 0x00000000 };
	static uint32 ZWInvMaskRaw[4] = { 0xffffffff, 0xffffffff, 0x00000000, 0x00000000 };

	__m128 XYInvMask = _mm_load_ps( (float*)XYInvMaskRaw );
	__m128 XZInvMask = _mm_load_ps( (float*)XZInvMaskRaw );
	__m128 XWInvMask = _mm_load_ps( (float*)XWInvMaskRaw );
	__m128 YZInvMask = _mm_load_ps( (float*)YZInvMaskRaw );
	__m128 YWInvMask = _mm_load_ps( (float*)YWInvMaskRaw );
	__m128 ZWInvMask = _mm_load_ps( (float*)ZWInvMaskRaw );
}