#pragma once

#include "Vector3.h"
#include "Constants.h"

template<int I>
Vector3 Vector3::Integer
(
)
{
	static Vector3 result = Vector3(_mm_set_ps(0.f, (float)I, (float)I, (float)I));
	return result;
}
template<int I1, int I2, int I3>
Vector3 Vector3::Integer
(
)
{
	static Vector3 result = Vector3(_mm_set_ps(0.f, (float)I3, (float)I2, (float)I1));
	return result;
}

template<int N, int D>
Vector3 Vector3::Fraction
(
)
{
	static_assert(D != 0, "Denominator in Vector3::Fraction must be nonzero");
	static Vector3 result = Vector3(_mm_set_ps(0.f, (float)N / (float)D, (float)N / (float)D, (float)N / (float)D));
	return result;
}
template<int N1, int D1, int N2, int D2, int N3, int D3>
Vector3 Vector3::Fraction
(
)
{
	static_assert(D1 != 0, "Denominator1 in Vector3::Fraction must be nonzero");
	static_assert(D2 != 0, "Denominator2 in Vector3::Fraction must be nonzero");
	static_assert(D3 != 0, "Denominator3 in Vector3::Fraction must be nonzero");
	static Vector3 result = Vector3(_mm_set_ps(0.f, (float)N3 / (float)D3, (float)N2 / (float)D2, (float)N1 / (float)D1));
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
	static Vector3 result = Vector3(_mm_set_ps(0.f, 1.f, 1.f, 1.f));
	return result;
}
Vector3 Vector3::Two
(
)
{
	static Vector3 result = Vector3(_mm_set_ps(0.f, 2.f, 2.f, 2.f));
	return result;
}
Vector3 Vector3::MinusOne
(
)
{
	static Vector3 result = Vector3(_mm_set_ps(0.f, -1.f, -1.f, -1.f));
	return result;
}
Vector3 Vector3::Half
(
)
{
	static Vector3 result = Vector3(_mm_set_ps(0.f, 0.5f, 0.5f, 0.5f));
	return result;
}
Vector3 Vector3::Quarter
(
)
{
	static Vector3 result = Vector3(_mm_set_ps(0.f, 0.25f, 0.25f, 0.25f));
	return result;
}
Vector3 Vector3::Pi
(
)
{
	static Vector3 result = Vector3(_mm_set_ps(0.f, PI, PI, PI));
	return result;
}
Vector3 Vector3::TwoPi
(
)
{
	static Vector3 result = Vector3(_mm_set_ps(0.f, TWO_PI, TWO_PI, TWO_PI));
	return result;
}
Vector3 Vector3::PiBy2
(
)
{
	static Vector3 result = Vector3(_mm_set_ps(0.f, PI_BY_2, PI_BY_2, PI_BY_2));
	return result;
}
Vector3 Vector3::PiBy4
(
)
{
	static Vector3 result = Vector3(_mm_set_ps(0.f, PI_BY_4, PI_BY_4, PI_BY_4));
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
	return Vector3(_mm_set_ps(0.f, _value[2], _value[1], _value[0]));
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
inline Vector3 Cross
(
	Vector3ConstRef _l, 
	Vector3ConstRef _r
)
{
	/*
	Vector3 return = 
		(
			l.y * r.z - l.z * r.y,
			l.z * r.x - l.x * r.z,
			l.x * r.y - l.y * r.x
		)
	*/
	return Vector3
	(
		_mm_sub_ps
		(
			_mm_mul_ps( _mm_shuffle_ps(_l.m_value, _l.m_value, _MM_SHUFFLE(3, 0, 2, 1)), _mm_shuffle_ps(_r.m_value, _r.m_value, _MM_SHUFFLE(3, 1, 0, 2)) ),
			_mm_mul_ps( _mm_shuffle_ps(_l.m_value, _l.m_value, _MM_SHUFFLE(3, 1, 0, 2)), _mm_shuffle_ps(_r.m_value, _r.m_value, _MM_SHUFFLE(3, 0, 2, 1)) )
		)
	);
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
	return And( Vector3(_mm_rcp_ps(_param.m_value)), VectorMasks::XYZMask );
}
inline Vector3 ReciprocalSqrt
(
	Vector3ConstRef _param
)
{
	return And( Vector3(_mm_rsqrt_ps(_param.m_value)), VectorMasks::XYZMask );
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
inline Vector3 Lerp
(
	Vector3ConstRef _a, 
	Vector3ConstRef _b, 
	Vector3ConstRef _lerpValue
)
{	
	return Vector3(_mm_add_ps(_mm_mul_ps(_a.m_value, _mm_sub_ps(Vector1::One().m_value, _lerpValue.m_value)), _mm_mul_ps(_b.m_value, _lerpValue.m_value)));
}
inline Vector3 Lerp
(
	Vector3ConstRef _a, 
	Vector3ConstRef _b, 
	Vector1ConstRef _lerpValue
)
{
	return Vector3(_mm_add_ps(_mm_mul_ps(_a.m_value, _mm_sub_ps(Vector1::One().m_value, _lerpValue.m_value)), _mm_mul_ps(_b.m_value, _lerpValue.m_value)));
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


inline bool IsNormalised
(
	Vector3ConstRef _param
)
{
	Vector1 lengthSq = Dot(_param, _param);
	return (Abs(lengthSq - Vector1::One()) < Vector1::Fraction<1, 10000>());
}