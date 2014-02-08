#pragma once

#include <xmmintrin.h>
#include <intrin.h>
#include <Core\Core.h>
#include <math.h>

class Vector1;
class Vector2;
class Vector3;
class Vector4;
class Matrix33;
class Matrix44;
class Quaternion;

typedef Vector1 const Vector1ConstParam;
typedef Vector1 const& Vector1ConstRef;
typedef Vector1& Vector1Ref;

typedef Vector2 const Vector2ConstParam;
typedef Vector2 const& Vector2ConstRef;
typedef Vector2& Vector2Ref;

typedef Vector3 const Vector3ConstParam;
typedef Vector3 const& Vector3ConstRef;
typedef Vector3& Vector3Ref;

typedef Vector4 const Vector4ConstParam;
typedef Vector4 const& Vector4ConstRef;
typedef Vector4& Vector4Ref;

typedef Matrix33 const Matrix33ConstParam;
typedef Matrix33 const& Matrix33ConstRef;
typedef Matrix33& Matrix33Ref;

typedef Matrix44 const Matrix44ConstParam;
typedef Matrix44 const& Matrix44ConstRef;
typedef Matrix44& Matrix44Ref;

typedef Quaternion const QuaternionConstParam;
typedef Quaternion const& QuaternionConstRef;
typedef Quaternion& QuaternionRef;

//union FloatSSE
//{
//	__m128 m_sse;
//	float m_float[4];
//};
//
//union UIntSSE
//{
//	__m128 m_sse;
//	uint32 m_uint[4];
//};

namespace VectorMasks
{
	extern __m128 PositiveMask;

	extern __m128 XMask;
	extern __m128 YMask;
	extern __m128 ZMask;
	extern __m128 WMask;
	
	extern __m128 XYMask;
	extern __m128 XZMask;
	extern __m128 XWMask;
	extern __m128 YZMask;
	extern __m128 YWMask;
	extern __m128 ZWMask;
	
	extern __m128 XYZMask;
	extern __m128 XYWMask;
	extern __m128 XZWMask;
	extern __m128 YZWMask;

	
	extern __m128 XInvMask;
	extern __m128 YInvMask;
	extern __m128 ZInvMask;
	extern __m128 WInvMask;

	extern __m128 XYInvMask;
	extern __m128 XZInvMask;
	extern __m128 XWInvMask;
	extern __m128 YZInvMask;
	extern __m128 YWInvMask;
	extern __m128 ZWInvMask;
	
	extern __m128 XYZInvMask;
	extern __m128 XYWInvMask;
	extern __m128 XZWInvMask;
	extern __m128 YZWInvMask;
}