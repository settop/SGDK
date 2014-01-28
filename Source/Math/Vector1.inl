#pragma once

#include "Vector1.h"
#include "Constants.h"

template<int I>
Vector1 Vector1::Integer
(
)
{
	static Vector1 result = Vector1(_mm_set_ps1((float)I));
	return result;
}
template<int N, int D>
Vector1 Vector1::Fraction
(
)
{
	static_assert(D != 0, "Denominator in Vector1::Fraction must be nonzero");
	static Vector1 result = Vector1(_mm_set_ps1((float)N / (float)D));
	return result;
}
Vector1 Vector1::Zero
(
)
{
	static Vector1 result = Vector1(_mm_set_ps1(0.f));
	return result;
}
Vector1 Vector1::One
(
)
{
	static Vector1 result = Vector1(_mm_set_ps1(1.f));
	return result;
}
Vector1 Vector1::Two
(
)
{
	static Vector1 result = Vector1(_mm_set_ps1(2.f));
	return result;
}
Vector1 Vector1::MinusOne
(
)
{
	static Vector1 result = Vector1(_mm_set_ps1(-1.f));
	return result;
}
Vector1 Vector1::Half
(
)
{
	static Vector1 result = Vector1(_mm_set_ps1(0.5f));
	return result;
}
Vector1 Vector1::Quarter
(
)
{
	static Vector1 result = Vector1(_mm_set_ps1(0.25f));
	return result;
}
Vector1 Vector1::Pi
(
)
{
	static Vector1 result = Vector1(_mm_set_ps1(PI));
	return result;
}
Vector1 Vector1::TwoPi
(
)
{
	static Vector1 result = Vector1(_mm_set_ps1(TWO_PI));
	return result;
}
Vector1 Vector1::PiBy2
(
)
{
	static Vector1 result = Vector1(_mm_set_ps1(PI_BY_2));
	return result;
}
Vector1 Vector1::PiBy4
(
)
{
	static Vector1 result = Vector1(_mm_set_ps1(PI_BY_4));
	return result;
}

//------------------------------------------------------------------------------

inline Vector1::Vector1
(
)
{
	//m_value = _mm_set_ps1(0.f);
}

inline Vector1::Vector1
(
	Vector1ConstRef _other
)
{
	m_value = _other.m_value;
}

inline Vector1Ref Vector1::operator=
(
	Vector1ConstRef _other
)
{
	m_value = _other.m_value;
	return *this;
}

inline Vector1::Vector1
(
	__m128 _value
)
{
	m_value = _value;
}

inline Vector1 LoadVector1
(
	float *_value
)
{
	Vector1 ret;
	ret.m_value = _mm_set_ps1(*_value);
	return ret;
}
inline void StoreVector1
(
	Vector1ConstRef _vector,
	float *_value
)
{
	__declspec(align(16)) float storedFloats[4];
	_mm_store_ps( storedFloats, _vector.m_value );
	_value[0] = storedFloats[0];
}

inline Vector1 operator+
(
	Vector1ConstRef _l, 
	Vector1ConstRef _r
)
{
	Vector1 ret;
	ret.m_value = _mm_add_ps(_l.m_value, _r.m_value);
	return ret;
}

inline Vector1 operator-
(
	Vector1ConstRef _l, 
	Vector1ConstRef _r
)
{
	Vector1 ret;
	ret.m_value = _mm_sub_ps(_l.m_value, _r.m_value);
	return ret;
}

inline Vector1 operator*
(
	Vector1ConstRef _l, 
	Vector1ConstRef _r
)
{
	Vector1 ret;
	ret.m_value = _mm_mul_ps(_l.m_value, _r.m_value);
	return ret;
}

inline Vector1 operator/
(
	Vector1ConstRef _l, 
	Vector1ConstRef _r
)
{
	Vector1 ret;
	ret.m_value = _mm_div_ps(_l.m_value, _r.m_value);
	return ret;
}

inline bool operator==
(
	Vector1ConstRef _l, 
	Vector1ConstRef _r
)
{
	__declspec(align(16)) uint32 storedBits[4];
	_mm_store_ps( (float*)storedBits, _mm_cmpeq_ss(_l.m_value, _r.m_value) );
	return storedBits[0] == 0xffffffff;
};
inline bool operator!=
(
	Vector1ConstRef _l, 
	Vector1ConstRef _r
)
{
	__declspec(align(16)) uint32 storedBits[4];
	_mm_store_ps( (float*)storedBits, _mm_cmpneq_ss(_l.m_value, _r.m_value) );
	return storedBits[0] == 0xffffffff;
};
inline bool operator>
(	
	Vector1ConstRef _l, 
	Vector1ConstRef _r
)
{
	__declspec(align(16)) uint32 storedBits[4];
	_mm_store_ps( (float*)storedBits, _mm_cmpgt_ss(_l.m_value, _r.m_value) );
	return storedBits[0] == 0xffffffff;
}
inline bool operator>=
(
	Vector1ConstRef _l, 
	Vector1ConstRef _r
)
{
	__declspec(align(16)) uint32 storedBits[4];
	_mm_store_ps( (float*)storedBits, _mm_cmpge_ss(_l.m_value, _r.m_value) );
	return storedBits[0] == 0xffffffff;
}
inline bool operator<
(
	Vector1ConstRef _l, 
	Vector1ConstRef _r
)
{
	__declspec(align(16)) uint32 storedBits[4];
	_mm_store_ps( (float*)storedBits, _mm_cmplt_ss(_l.m_value, _r.m_value) );
	return storedBits[0] == 0xffffffff;
}
inline bool operator<=
(
	Vector1ConstRef _l, 
	Vector1ConstRef _r
)
{
	__declspec(align(16)) uint32 storedBits[4];
	_mm_store_ps( (float*)storedBits, _mm_cmple_ss(_l.m_value, _r.m_value) );
	return storedBits[0] == 0xffffffff;
}

inline Vector1 Dot
(
	Vector1ConstRef _l, 
	Vector1ConstRef _r
)
{
	Vector1 ret;
	ret.m_value = _mm_mul_ps(_l.m_value, _r.m_value);
	return ret;
}
inline Vector1 Length
(
	Vector1ConstRef _param
)
{
	return _param;
}
inline Vector1 Abs
(
	Vector1ConstRef _param
)
{
	return Vector1(_mm_and_ps(_param.m_value, VectorMasks::PositiveMask));
}
inline Vector1 Sqrt
(
	Vector1ConstRef _param
)
{
	Vector1 ret;
	ret.m_value = _mm_sqrt_ps(_param.m_value);
	return ret;
}
inline Vector1 Reciprocal
(
	Vector1ConstRef _param
)
{
	Vector1 ret;
	ret.m_value = _mm_rcp_ps(_param.m_value);
	return ret;
}
inline Vector1 ReciprocalSqrt
(
	Vector1ConstRef _param
)
{
	Vector1 ret;
	ret.m_value = _mm_rsqrt_ps(_param.m_value);
	return ret;
}
inline Vector1 Min
(
	Vector1ConstRef _a,
	Vector1ConstRef _b
)
{
	Vector1 ret;
	ret.m_value = _mm_min_ps(_a.m_value, _b.m_value);
	return ret;
}
inline Vector1 Max
(
	Vector1ConstRef _a, 
	Vector1ConstRef _b
)
{
	Vector1 ret;
	ret.m_value = _mm_max_ps(_a.m_value, _b.m_value);
	return ret;
}
inline Vector1 And
(
	Vector1ConstRef _a, 
	Vector1ConstRef _b
)
{
	Vector1 ret;
	ret.m_value = _mm_and_ps(_a.m_value, _b.m_value);
	return ret;
}
inline Vector1 Or
(
	Vector1ConstRef _a, 
	Vector1ConstRef _b
)
{
	Vector1 ret;
	ret.m_value = _mm_or_ps(_a.m_value, _b.m_value);
	return ret;
}
inline Vector1 Xor
(
	Vector1ConstRef _a, 
	Vector1ConstRef _b
)
{
	Vector1 ret;
	ret.m_value = _mm_xor_ps(_a.m_value, _b.m_value);
	return ret;
}