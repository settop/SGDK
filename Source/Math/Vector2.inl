#pragma once

#include "Vector2.h"
#include "Constants.h"

template<int I>
Vector2 Vector2::Integer
(
)
{
	static Vector2 result = Vector2(_mm_set_ps(0.f, 0.f, (float)I, (float)I));
	return result;
}

template<int I1, int I2>
Vector2 Vector2::Integer
(
)
{
	static Vector2 result = Vector2(_mm_set_ps(0.f, 0.f, (float)I2, (float)I1));
	return result;
}

template<int N, int D>
Vector2 Vector2::Fraction
(
)
{
	static_assert(D != 0, "Denominator in Vector2::Fraction must be nonzero");
	static Vector2 result = Vector2(_mm_set_ps(0.f, 0.f, (float)N / (float)D, (float)N / (float)D));
	return result;
}

template<int N1, int D1, int N2, int D2>
Vector2 Fraction
(
)
{
	static_assert(D1 != 0, "Denominator1 in Vector2::Fraction must be nonzero");
	static_assert(D2 != 0, "Denominator2 in Vector2::Fraction must be nonzero");
	static Vector2 result = Vector2(_mm_set_ps(0.f, 0.f, (float)N2 / (float)D2, (float)N1 / (float)D1));
	return result;
}

Vector2 Vector2::Zero
(
)
{
	static Vector2 result = Vector2(_mm_set_ps(0.f, 0.f, 0.f, 0.f));
	return result;
}
Vector2 Vector2::One
(
)
{
	static Vector2 result = Vector2(_mm_set_ps(0.f, 0.f, 1.f, 1.f));
	return result;
}
Vector2 Vector2::Two
(
)
{
	static Vector2 result = Vector2(_mm_set_ps(0.f, 0.f, 2.f, 2.f));
	return result;
}
Vector2 Vector2::MinusOne
(
)
{
	static Vector2 result = Vector2(_mm_set_ps(0.f, 0.f, -1.f, -1.f));
	return result;
}
Vector2 Vector2::Half
(
)
{
	static Vector2 result = Vector2(_mm_set_ps(0.f, 0.f, 0.5f, 0.5f));
	return result;
}
Vector2 Vector2::Quarter
(
)
{
	static Vector2 result = Vector2(_mm_set_ps(0.f, 0.f, 0.25f, 0.25f));
	return result;
}
Vector2 Vector2::Pi
(
)
{
	static Vector2 result = Vector2(_mm_set_ps(0.f, 0.f, PI, PI));
	return result;
}
Vector2 Vector2::TwoPi
(
)
{
	static Vector2 result = Vector2(_mm_set_ps(0.f, 0.f, TWO_PI, TWO_PI));
	return result;
}
Vector2 Vector2::PiBy2
(
)
{
	static Vector2 result = Vector2(_mm_set_ps(0.f, 0.f, PI_BY_2, PI_BY_2));
	return result;
}
Vector2 Vector2::PiBy4
(
)
{
	static Vector2 result = Vector2(_mm_set_ps(0.f, 0.f, PI_BY_4, PI_BY_4));
	return result;
}

//------------------------------------------------------------------------------

inline Vector2::Vector2
(
)
{
	//m_value = _mm_set_ps1(0.f);
}

inline Vector2::Vector2
(
	Vector1ConstRef _x, 
	Vector1ConstRef _y
)
{
	__m128 x = _mm_and_ps(_x.m_value, VectorMasks::XMask);
	__m128 y = _mm_and_ps(_y.m_value, VectorMasks::YMask);
	m_value = _mm_or_ps(x, y);
}

inline Vector2::Vector2
(
	Vector2ConstRef _other
)
{
	m_value = _other.m_value;
}

inline Vector2Ref Vector2::operator=
(
	Vector2ConstRef _other
)
{
	m_value = _other.m_value;
	return *this;
}

inline Vector1 Vector2::GetX
(
) const
{
	Vector1 ret;
	ret.m_value = _mm_shuffle_ps(m_value, m_value, _MM_SHUFFLE(0, 0, 0, 0));
	return ret;
}

inline Vector1 Vector2::GetY
(
) const
{
	Vector1 ret;
	ret.m_value = _mm_shuffle_ps(m_value, m_value, _MM_SHUFFLE(1, 1, 1, 1));
	return ret;
}

inline void Vector2::SetX
(
	Vector1ConstRef _x
)
{
	__m128 l = _mm_and_ps(m_value, VectorMasks::YMask);
	__m128 r = _mm_and_ps(_x.m_value, VectorMasks::XMask);
	m_value = _mm_or_ps(l, r);
};

inline void Vector2::SetY
(
	Vector1ConstRef _y
)
{
	__m128 l = _mm_and_ps(m_value, VectorMasks::XMask);
	__m128 r = _mm_and_ps(_y.m_value, VectorMasks::YMask);
	m_value = _mm_or_ps(l, r);
}

inline Vector2::Vector2
(
	__m128 _value
)
{
	m_value = _value;
}

inline Vector2 LoadVector2
(
	float *_value
)
{
	return Vector2(_mm_set_ps(0.f, 0.f, _value[1], _value[0]));
}
inline void StoreVector2
(
	Vector2ConstRef _vector,
	float *_value
)
{
	__declspec(align(16)) float storedFloats[4];
	_mm_store_ps( storedFloats, _vector.m_value );
	_value[0] = storedFloats[0];
	_value[1] = storedFloats[1];
}

inline Vector2 operator+
(
	Vector2ConstRef _l, 
	Vector2ConstRef _r
)
{
	return Vector2(_mm_add_ps(_l.m_value, _r.m_value));
}

inline Vector2 operator-
(
	Vector2ConstRef _l, 
	Vector2ConstRef _r
)
{
	return Vector2(_mm_sub_ps(_l.m_value, _r.m_value));
}

inline Vector2 operator*
(
	Vector2ConstRef _l, 
	Vector1ConstRef _r
)
{
	return Vector2(_mm_mul_ps(_l.m_value, _r.m_value));
}

inline Vector2 operator*
(
	Vector1ConstRef _l, 
	Vector2ConstRef _r
)
{
	return Vector2(_mm_mul_ps(_l.m_value, _r.m_value));
}

inline Vector2 operator/
(
	Vector2ConstRef _l, 
	Vector1ConstRef _r
)
{
	return Vector2(_mm_div_ps(_l.m_value, _r.m_value));
}

inline bool operator==
(
	Vector2ConstRef _l, 
	Vector2ConstRef _r
)
{
	__declspec(align(16)) uint32 storedBits[4];
	_mm_store_ps( (float*)storedBits, _mm_cmpeq_ss(_l.m_value, _r.m_value) );
	return storedBits[0] == 0xffffffff && storedBits[1] == 0xffffffff;
};
inline bool operator!=
(
	Vector2ConstRef _l, 
	Vector2ConstRef _r
)
{
	__declspec(align(16)) uint32 storedBits[4];
	_mm_store_ps( (float*)storedBits, _mm_cmpneq_ss(_l.m_value, _r.m_value) );
	return storedBits[0] == 0xffffffff && storedBits[1] == 0xffffffff;
};

inline Vector1 Dot
(
	Vector2ConstRef _l, 
	Vector2ConstRef _r
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
	Vector2ConstRef _param
)
{
	return Sqrt(Dot(_param, _param));
};
inline Vector2 Abs
(
	Vector2ConstRef _param
)
{	
	return Vector2(_mm_and_ps(_param.m_value, VectorMasks::PositiveMask));
}
inline Vector2 Sqrt
(
	Vector2ConstRef _param
)
{
	return Vector2(_mm_sqrt_ps(_param.m_value));
}
inline Vector2 Reciprocal
(
	Vector2ConstRef _param
)
{
	return And( Vector2(_mm_rcp_ps(_param.m_value)), VectorMasks::XYMask );
}
inline Vector2 ReciprocalSqrt
(
	Vector2ConstRef _param
)
{
	return And( Vector2(_mm_rsqrt_ps(_param.m_value)), VectorMasks::XYMask );
}
inline Vector2 Min
(
	Vector2ConstRef _a,
	Vector2ConstRef _b
)
{
	return Vector2(_mm_min_ps(_a.m_value, _b.m_value));
}
inline Vector2 Max
(
	Vector2ConstRef _a, 
	Vector2ConstRef _b
)
{
	return Vector2(_mm_max_ps(_a.m_value, _b.m_value));
}
inline Vector2 And
(
	Vector2ConstRef _a, 
	Vector2ConstRef _b
)
{
	return Vector2(_mm_and_ps(_a.m_value, _b.m_value));
}
inline Vector2 Or
(
	Vector2ConstRef _a, 
	Vector2ConstRef _b
)
{
	return Vector2(_mm_or_ps(_a.m_value, _b.m_value));
}
inline Vector2 Xor
(
	Vector2ConstRef _a, 
	Vector2ConstRef _b
)
{
	return Vector2(_mm_xor_ps(_a.m_value, _b.m_value));
}