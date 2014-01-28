#pragma once

#include "Vector4.h"
#include "Constants.h"

template<int I>
Vector4 Vector4::Integer
(
)
{
	static Vector4 result = Vector4(_mm_set_ps((float)I, (float)I, (float)I, (float)I));
	return result;
}
template<int I1, int I2, int I3, int I4>
Vector4 Vector4::Integer
(
)
{
	static Vector4 result = Vector4(_mm_set_ps((float)I4, (float)I3, (float)I2, (float)I1));
	return result;
}

template<int N, int D>
Vector4 Vector4::Fraction
(
)
{
	static_assert(D != 0, "Denominator in Vector4::Fraction must be nonzero");
	static Vector4 result = Vector4(_mm_set_ps((float)N / (float)D, (float)N / (float)D, (float)N / (float)D, (float)N / (float)D));
	return result;
}
	template<int N1, int D1, int N2, int D2, int N3, int D3, int N4, int D4>
Vector4 Vector4::Fraction
(
)
{
	static_assert(D1 != 0, "Denominator1 in Vector4::Fraction must be nonzero");
	static_assert(D2 != 0, "Denominator2 in Vector4::Fraction must be nonzero");
	static_assert(D3 != 0, "Denominator3 in Vector4::Fraction must be nonzero");
	static_assert(D4 != 0, "Denominator4 in Vector4::Fraction must be nonzero");
	static Vector4 result = Vector4(_mm_set_ps((float)N4 / (float)D4, (float)N3 / (float)D3, (float)N2 / (float)D2, (float)N1 / (float)D1));
	return result;
}

Vector4 Vector4::Zero
(
)
{
	static Vector4 result = Vector4(_mm_set_ps(0.f, 0.f, 0.f, 0.f));
	return result;
}
Vector4 Vector4::One
(
)
{
	static Vector4 result = Vector4(_mm_set_ps(1.f, 1.f, 1.f, 1.f));
	return result;
}
Vector4 Vector4::Two
(
)
{
	static Vector4 result = Vector4(_mm_set_ps(2.f, 2.f, 2.f, 2.f));
	return result;
}
Vector4 Vector4::MinusOne
(
)
{
	static Vector4 result = Vector4(_mm_set_ps(-1.f, -1.f, -1.f, -1.f));
	return result;
}
Vector4 Vector4::Half
(
)
{
	static Vector4 result = Vector4(_mm_set_ps(0.5f, 0.5f, 0.5f, 0.5f));
	return result;
}
Vector4 Vector4::Quarter
(
)
{
	static Vector4 result = Vector4(_mm_set_ps(0.25f, 0.25f, 0.25f, 0.25f));
	return result;
}
Vector4 Vector4::Pi
(
)
{
	static Vector4 result = Vector4(_mm_set_ps(PI, PI, PI, PI));
	return result;
}
Vector4 Vector4::TwoPi
(
)
{
	static Vector4 result = Vector4(_mm_set_ps(TWO_PI, TWO_PI, TWO_PI, TWO_PI));
	return result;
}
Vector4 Vector4::PiBy2
(
)
{
	static Vector4 result = Vector4(_mm_set_ps(PI_BY_2, PI_BY_2, PI_BY_2, PI_BY_2));
	return result;
}
Vector4 Vector4::PiBy4
(
)
{
	static Vector4 result = Vector4(_mm_set_ps(PI_BY_4, PI_BY_4, PI_BY_4, PI_BY_4));
	return result;
}

//------------------------------------------------------------------------------

inline Vector4::Vector4
(
)
{
	//m_value = _mm_set_ps1(0.f);
}

inline Vector4::Vector4
(
	Vector1ConstRef _x, 
	Vector1ConstRef _y, 
	Vector1ConstRef _z, 
	Vector1ConstRef _w
)
{
	__m128 x = _mm_and_ps(_x.m_value, VectorMasks::XMask);
	__m128 y = _mm_and_ps(_y.m_value, VectorMasks::YMask);
	__m128 z = _mm_and_ps(_z.m_value, VectorMasks::ZMask);
	__m128 w = _mm_and_ps(_w.m_value, VectorMasks::WMask);
	m_value = _mm_or_ps(_mm_or_ps(x, y), _mm_or_ps(z, w));
}

inline Vector4::Vector4
(
	Vector2ConstRef _xy, 
	Vector1ConstRef _z, 
	Vector1ConstRef _w
)
{
	__m128 xy = _mm_and_ps(_xy.m_value, VectorMasks::XYMask);
	__m128 z = _mm_and_ps(_z.m_value, VectorMasks::ZMask);
	__m128 w = _mm_and_ps(_w.m_value, VectorMasks::WMask);
	m_value = _mm_or_ps(xy, _mm_or_ps(z, w));
}

inline Vector4::Vector4
(
	Vector3ConstRef _xyz,  
	Vector1ConstRef _w
)
{
	__m128 xyz = _mm_and_ps(_xyz.m_value, VectorMasks::XYZMask);
	__m128 w = _mm_and_ps(_w.m_value, VectorMasks::WMask);
	m_value = _mm_or_ps(xyz, w);
}

inline Vector4::Vector4
(
	Vector4ConstRef _other
)
{
	m_value = _other.m_value;
}

inline Vector4Ref Vector4::operator=
(
	Vector4ConstRef _other
)
{
	m_value = _other.m_value;
	return *this;
}

inline Vector1 Vector4::GetX
(
) const
{
	Vector1 ret;
	ret.m_value = _mm_shuffle_ps(m_value, m_value, _MM_SHUFFLE(0, 0, 0, 0));
	return ret;
}

inline Vector1 Vector4::GetY
(
) const
{
	Vector1 ret;
	ret.m_value = _mm_shuffle_ps(m_value, m_value, _MM_SHUFFLE(1, 1, 1, 1));
	return ret;
}

inline Vector1 Vector4::GetZ
(
) const
{
	Vector1 ret;
	ret.m_value = _mm_shuffle_ps(m_value, m_value, _MM_SHUFFLE(2, 2, 2, 2));
	return ret;
}

inline Vector1 Vector4::GetW
(
) const
{
	Vector1 ret;
	ret.m_value = _mm_shuffle_ps(m_value, m_value, _MM_SHUFFLE(3, 3, 3, 3));
	return ret;
}

inline void Vector4::SetX
(
	Vector1ConstRef _x
)
{
	__m128 l = _mm_and_ps(m_value, VectorMasks::YZWMask);
	__m128 r = _mm_and_ps(_x.m_value, VectorMasks::XMask);
	m_value = _mm_or_ps(l, r);
};

inline void Vector4::SetY
(
	Vector1ConstRef _y
)
{
	__m128 l = _mm_and_ps(m_value, VectorMasks::XZWMask);
	__m128 r = _mm_and_ps(_y.m_value, VectorMasks::YMask);
	m_value = _mm_or_ps(l, r);
}

inline void Vector4::SetZ
(
	Vector1ConstRef _z
)
{
	__m128 l = _mm_and_ps(m_value, VectorMasks::XYWMask);
	__m128 r = _mm_and_ps(_z.m_value, VectorMasks::ZMask);
	m_value = _mm_or_ps(l, r);
}

inline void Vector4::SetW
(
	Vector1ConstRef _w
)
{
	__m128 l = _mm_and_ps(m_value, VectorMasks::XYZMask);
	__m128 r = _mm_and_ps(_w.m_value, VectorMasks::WMask);
	m_value = _mm_or_ps(l, r);
}

inline Vector4::Vector4
(
	__m128 _value
)
{
	m_value = _value;
}

inline Vector4 LoadVector4
(
	float *_value
)
{
	return Vector4(_mm_set_ps(_value[3], _value[2], _value[1], _value[0]));
}
inline void StoreVector4
(
	Vector4ConstRef _vector,
	float *_value
)
{
	__declspec(align(16)) float storedFloats[4];
	_mm_store_ps( storedFloats, _vector.m_value );
	_value[0] = storedFloats[0];
	_value[1] = storedFloats[1];
	_value[2] = storedFloats[2];
	_value[3] = storedFloats[3];
}

inline Vector4 operator+
(
	Vector4ConstRef _l, 
	Vector4ConstRef _r
)
{
	return Vector4(_mm_add_ps(_l.m_value, _r.m_value));
}

inline Vector4 operator-
(
	Vector4ConstRef _l, 
	Vector4ConstRef _r
)
{
	return Vector4(_mm_sub_ps(_l.m_value, _r.m_value));
}

inline Vector4 operator*
(
	Vector4ConstRef _l, 
	Vector1ConstRef _r
)
{
	return Vector4(_mm_mul_ps(_l.m_value, _r.m_value));
}

inline Vector4 operator*
(
	Vector1ConstRef _l, 
	Vector4ConstRef _r
)
{
	return Vector4(_mm_mul_ps(_l.m_value, _r.m_value));
}

inline Vector4 operator/
(
	Vector4ConstRef _l, 
	Vector1ConstRef _r
)
{
	return Vector4(_mm_div_ps(_l.m_value, _r.m_value));
}

inline bool operator==
(
	Vector4ConstRef _l, 
	Vector4ConstRef _r
)
{
	__declspec(align(16)) uint32 storedBits[4];
	_mm_store_ps( (float*)storedBits, _mm_cmpeq_ss(_l.m_value, _r.m_value) );
	return storedBits[0] == 0xffffffff && storedBits[1] == 0xffffffff && storedBits[2] == 0xffffffff && storedBits[3] == 0xffffffff;
};
inline bool operator!=
(
	Vector4ConstRef _l, 
	Vector4ConstRef _r
)
{
	__declspec(align(16)) uint32 storedBits[4];
	_mm_store_ps( (float*)storedBits, _mm_cmpneq_ss(_l.m_value, _r.m_value) );
	return storedBits[0] == 0xffffffff && storedBits[1] == 0xffffffff && storedBits[2] == 0xffffffff && storedBits[3] == 0xffffffff;
};

inline Vector1 Dot
(
	Vector4ConstRef _l, 
	Vector4ConstRef _r
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
	Vector4ConstRef _param
)
{
	return Sqrt(Dot(_param, _param));
};
inline Vector4 Abs
(
	Vector4ConstRef _param
)
{	
	return Vector4(_mm_and_ps(_param.m_value, VectorMasks::PositiveMask));
}
inline Vector4 Sqrt
(
	Vector4ConstRef _param
)
{
	return Vector4(_mm_sqrt_ps(_param.m_value));
}
inline Vector4 Reciprocal
(
	Vector4ConstRef _param
)
{
	return And( Vector4(_mm_rcp_ps(_param.m_value)), VectorMasks::XYMask );
}
inline Vector4 ReciprocalSqrt
(
	Vector4ConstRef _param
)
{
	return And( Vector4(_mm_rsqrt_ps(_param.m_value)), VectorMasks::XYMask );
}
inline Vector4 Min
(
	Vector4ConstRef _a,
	Vector4ConstRef _b
)
{
	return Vector4(_mm_min_ps(_a.m_value, _b.m_value));
}
inline Vector4 Max
(
	Vector4ConstRef _a, 
	Vector4ConstRef _b
)
{
	return Vector4(_mm_max_ps(_a.m_value, _b.m_value));
}
inline Vector4 And
(
	Vector4ConstRef _a, 
	Vector4ConstRef _b
)
{
	return Vector4(_mm_and_ps(_a.m_value, _b.m_value));
}
inline Vector4 Or
(
	Vector4ConstRef _a, 
	Vector4ConstRef _b
)
{
	return Vector4(_mm_or_ps(_a.m_value, _b.m_value));
}
inline Vector4 Xor
(
	Vector4ConstRef _a, 
	Vector4ConstRef _b
)
{
	return Vector4(_mm_xor_ps(_a.m_value, _b.m_value));
}