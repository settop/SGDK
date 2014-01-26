#pragma once

#include "Vector3.h"
#include "Constants.h"

template<int I>
Vector3 Integer
(
)
{
	static Vector3 result = Vector3(_mm_set_ps((float)I, (float)I, (float)I, 0.f));
	return result;
}
template<int N, int D>
Vector3 Vector3::Fraction
(
)
{
	static_assert(D != 0, "Denominator in Vector3::Fraction must be nonzero");
	static Vector3 result = Vector3(_mm_set_ps((float)N / (float)D, (float)N / (float)D, (float)N / (float)D, 0.f));
	return result;
}
Vector3 Vector3::Zero
(
)
{
	static Vector3 result = Vector3(_mm_set_ps(0.f, 0.f, 0.f, 0.f));
	return result;
}
Vector3 Vector3::One
(
)
{
	static Vector3 result = Vector3(_mm_set_ps(1.f, 1.f, 1.f, 0.f));
	return result;
}
Vector3 Vector3::Two
(
)
{
	static Vector3 result = Vector3(_mm_set_ps(2.f, 2.f, 2.f, 0.f));
	return result;
}
Vector3 Vector3::MinusOne
(
)
{
	static Vector3 result = Vector3(_mm_set_ps(-1.f, -1.f, -1.f, 0.f));
	return result;
}
Vector3 Vector3::Half
(
)
{
	static Vector3 result = Vector3(_mm_set_ps(0.5f, 0.5f, 0.5f, 0.f));
	return result;
}
Vector3 Vector3::Quarter
(
)
{
	static Vector3 result = Vector3(_mm_set_ps(0.25f, 0.25f, 0.25f, 0.f));
	return result;
}
Vector3 Vector3::Pi
(
)
{
	static Vector3 result = Vector3(_mm_set_ps(PI, PI, PI, 0.f));
	return result;
}
Vector3 Vector3::TwoPi
(
)
{
	static Vector3 result = Vector3(_mm_set_ps(TWO_PI, TWO_PI, TWO_PI, 0.f));
	return result;
}
Vector3 Vector3::PiBy2
(
)
{
	static Vector3 result = Vector3(_mm_set_ps(PI_BY_2, PI_BY_2, PI_BY_2, 0.f));
	return result;
}
Vector3 Vector3::PiBy4
(
)
{
	static Vector3 result = Vector3(_mm_set_ps(PI_BY_4, PI_BY_4, PI_BY_4, 0.f));
	return result;
}

//------------------------------------------------------------------------------

inline Vector3::Vector3
(
)
{
	//m_value = _mm_set_ps1(0.f);
}

inline Vector3::Vector3
(
	Vector1ConstRef _x, 
	Vector1ConstRef _y, 
	Vector1ConstRef _z
)
{
	__m128 x = _mm_and_ps(_x.m_value, VectorMasks::XMask);
	__m128 y = _mm_and_ps(_y.m_value, VectorMasks::YMask);
	__m128 z = _mm_and_ps(_z.m_value, VectorMasks::ZMask);
	m_value = _mm_or_ps(x, _mm_or_ps(y, z));
}

inline Vector3::Vector3
(
	Vector2ConstRef _xy, 
	Vector1ConstRef _z
)
{
	__m128 xy = _mm_and_ps(_xy.m_value, VectorMasks::XYMask);
	__m128 z = _mm_and_ps(_z.m_value, VectorMasks::ZMask);
	m_value = _mm_or_ps(xy, z);
}

inline Vector3::Vector3
(
	Vector3ConstRef _other
)
{
	m_value = _other.m_value;
}

inline Vector3Ref Vector3::operator=
(
	Vector3ConstRef _other
)
{
	m_value = _other.m_value;
	return *this;
}

inline Vector1 Vector3::GetX
(
) const
{
	Vector1 ret;
	ret.m_value = _mm_shuffle_ps(m_value, m_value, _MM_SHUFFLE(0, 0, 0, 0));
	return ret;
}

inline Vector1 Vector3::GetY
(
) const
{
	Vector1 ret;
	ret.m_value = _mm_shuffle_ps(m_value, m_value, _MM_SHUFFLE(1, 1, 1, 1));
	return ret;
}

inline Vector1 Vector3::GetZ
(
) const
{
	Vector1 ret;
	ret.m_value = _mm_shuffle_ps(m_value, m_value, _MM_SHUFFLE(2, 2, 2, 2));
	return ret;
}

inline void Vector3::SetX
(
	Vector1ConstRef _x
)
{
	__m128 l = _mm_and_ps(m_value, VectorMasks::YZMask);
	__m128 r = _mm_and_ps(_x.m_value, VectorMasks::XMask);
	m_value = _mm_or_ps(l, r);
};

inline void Vector3::SetY
(
	Vector1ConstRef _y
)
{
	__m128 l = _mm_and_ps(m_value, VectorMasks::XZMask);
	__m128 r = _mm_and_ps(_y.m_value, VectorMasks::YMask);
	m_value = _mm_or_ps(l, r);
}

inline void Vector3::SetZ
(
	Vector1ConstRef _z
)
{
	__m128 l = _mm_and_ps(m_value, VectorMasks::XYMask);
	__m128 r = _mm_and_ps(_z.m_value, VectorMasks::ZMask);
	m_value = _mm_or_ps(l, r);
}

inline Vector3::Vector3
(
	__m128 _value
)
{
	m_value = _value;
}

inline Vector3 LoadVector3
(
	float *_value
)
{
	return Vector3(_mm_set_ps(_value[0], _value[1], _value[2], 0.f));
}
inline void StoreVector3
(
	Vector3ConstRef _vector,
	float *_value
)
{
	__declspec(align(16)) float storedFloats[4];
	_mm_store_ps( storedFloats, _vector.m_value );
	_value[0] = storedFloats[0];
	_value[1] = storedFloats[1];
	_value[2] = storedFloats[2];
}

inline Vector3 operator+
(
	Vector3ConstRef _l, 
	Vector3ConstRef _r
)
{
	return Vector3(_mm_add_ps(_l.m_value, _r.m_value));
}

inline Vector3 operator-
(
	Vector3ConstRef _l, 
	Vector3ConstRef _r
)
{
	return Vector3(_mm_sub_ps(_l.m_value, _r.m_value));
}

inline Vector3 operator*
(
	Vector3ConstRef _l, 
	Vector1ConstRef _r
)
{
	return Vector3(_mm_mul_ps(_l.m_value, _r.m_value));
}

inline Vector3 operator*
(
	Vector1ConstRef _l, 
	Vector3ConstRef _r
)
{
	return Vector3(_mm_mul_ps(_l.m_value, _r.m_value));
}

inline Vector3 operator/
(
	Vector3ConstRef _l, 
	Vector1ConstRef _r
)
{
	return Vector3(_mm_div_ps(_l.m_value, _r.m_value));
}

inline bool operator==
(
	Vector3ConstRef _l, 
	Vector3ConstRef _r
)
{
	__declspec(align(16)) uint32 storedBits[4];
	_mm_store_ps( (float*)storedBits, _mm_cmpeq_ss(_l.m_value, _r.m_value) );
	return storedBits[0] == 0xffffffff && storedBits[1] == 0xffffffff && storedBits[2] == 0xffffffff;
};
inline bool operator!=
(
	Vector3ConstRef _l, 
	Vector3ConstRef _r
)
{
	__declspec(align(16)) uint32 storedBits[4];
	_mm_store_ps( (float*)storedBits, _mm_cmpneq_ss(_l.m_value, _r.m_value) );
	return storedBits[0] == 0xffffffff && storedBits[1] == 0xffffffff && storedBits[2] == 0xffffffff;
};

inline Vector1 Dot
(
	Vector3ConstRef _l, 
	Vector3ConstRef _r
)
{
	__m128 r1, r2, r3;
	r1 = _mm_mul_ps(_l.m_value, _r.m_value);
	r2 = _mm_hadd_ps(r1, r1);
	r3 = _mm_hadd_ps(r2, r2);
	return Vector1(r3);
}
inline Vector1 Length
(
	Vector3ConstRef _param
)
{
	return Sqrt(Dot(_param, _param));
};
inline Vector3 Abs
(
	Vector3ConstRef _param
)
{	
	return Vector3(_mm_and_ps(_param.m_value, VectorMasks::PositiveMask));
}
inline Vector3 Sqrt
(
	Vector3ConstRef _param
)
{
	return Vector3(_mm_sqrt_ps(_param.m_value));
}
inline Vector3 Reciprocal
(
	Vector3ConstRef _param
)
{
	return And( Vector3(_mm_rcp_ps(_param.m_value)), VectorMasks::XYMask );
}
inline Vector3 ReciprocalSqrt
(
	Vector3ConstRef _param
)
{
	return And( Vector3(_mm_rsqrt_ps(_param.m_value)), VectorMasks::XYMask );
}
inline Vector3 Min
(
	Vector3ConstRef _a,
	Vector3ConstRef _b
)
{
	return Vector3(_mm_min_ps(_a.m_value, _b.m_value));
}
inline Vector3 Max
(
	Vector3ConstRef _a, 
	Vector3ConstRef _b
)
{
	return Vector3(_mm_max_ps(_a.m_value, _b.m_value));
}
inline Vector3 And
(
	Vector3ConstRef _a, 
	Vector3ConstRef _b
)
{
	return Vector3(_mm_and_ps(_a.m_value, _b.m_value));
}
inline Vector3 Or
(
	Vector3ConstRef _a, 
	Vector3ConstRef _b
)
{
	return Vector3(_mm_or_ps(_a.m_value, _b.m_value));
}
inline Vector3 Xor
(
	Vector3ConstRef _a, 
	Vector3ConstRef _b
)
{
	return Vector3(_mm_xor_ps(_a.m_value, _b.m_value));
}