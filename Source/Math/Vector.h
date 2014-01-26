#pragma once

#include <xmmintrin.h>
#include <intrin.h>
#include <Core\Core.h>

class Vector1;
class Vector2;
class Vector3;
class Vector4;

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

#define VectorFriends( _Vector )\
	friend class Vector1;\
	friend class Vector2;\
	friend class Vector3;\
	friend class Vector4;\
	\
	friend _Vector Load##_Vector(float *_value);\
	friend void Store##_Vector(_Vector##ConstRef _vector, float *_value);\
	\
	friend _Vector operator+(_Vector##ConstRef _l, _Vector##ConstRef _r);\
	friend _Vector operator-(_Vector##ConstRef _l, _Vector##ConstRef _r);\
	friend Vector1 operator*(Vector1ConstRef _l, Vector1ConstRef _r);\
	friend Vector2 operator*(Vector2ConstRef _l, Vector1ConstRef _r);\
	friend Vector3 operator*(Vector3ConstRef _l, Vector1ConstRef _r);\
	friend Vector4 operator*(Vector4ConstRef _l, Vector1ConstRef _r);\
	friend Vector1 operator*(Vector1ConstRef _l, Vector1ConstRef _r);\
	friend Vector2 operator*(Vector1ConstRef _l, Vector2ConstRef _r);\
	friend Vector3 operator*(Vector1ConstRef _l, Vector3ConstRef _r);\
	friend Vector4 operator*(Vector1ConstRef _l, Vector4ConstRef _r);\
	friend Vector1 operator/(Vector1ConstRef _l, Vector1ConstRef _r);\
	friend Vector2 operator/(Vector2ConstRef _l, Vector1ConstRef _r);\
	friend Vector3 operator/(Vector3ConstRef _l, Vector1ConstRef _r);\
	friend Vector4 operator/(Vector4ConstRef _l, Vector1ConstRef _r);\
	\
	friend bool operator==(_Vector##ConstRef _l, _Vector##ConstRef _r);\
	friend bool operator!=(_Vector##ConstRef _l, _Vector##ConstRef _r);\
	\
	friend Vector1 Dot(_Vector##ConstRef _l, _Vector##ConstRef _r);\
	friend Vector1 Length(_Vector##ConstRef _param);\
	friend _Vector Abs(_Vector##ConstRef _param);\
	friend _Vector Sqrt(_Vector##ConstRef _param);\
	friend _Vector Reciprocal(_Vector##ConstRef _param);\
	friend _Vector ReciprocalSqrt(_Vector##ConstRef _param);\
	friend _Vector Min(_Vector##ConstRef _a, _Vector##ConstRef _b);\
	friend _Vector Max(_Vector##ConstRef _a, _Vector##ConstRef _b);\
	friend _Vector And(_Vector##ConstRef _a, _Vector##ConstRef _b);\
	friend _Vector Or(_Vector##ConstRef _a, _Vector##ConstRef _b);\
	friend _Vector Xor(_Vector##ConstRef _a, _Vector##ConstRef _b);

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
}