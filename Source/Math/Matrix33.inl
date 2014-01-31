#pragma once

#include "Matrix33.h"

template<int I>
Matrix33 Matrix33::Integer
(
)
{
	static Matrix33 result = Matrix33(Vector3::Integer<I, 0, 0>(), Vector3::Integer<0, I, 0>(), Vector3::Integer<0, 0, I>());
	return result;
};
Matrix33 Matrix33::Identity
(
)
{
	static Matrix33 result = Matrix33(Vector3::Integer<1, 0, 0>(), Vector3::Integer<0, 1, 0>(), Vector3::Integer<0, 0, 1>());
	return result;
};
Matrix33 Matrix33::Zero
(
)
{
	static Matrix33 result = Matrix33(Vector3::Zero(), Vector3::Zero(), Vector3::Zero());
	return result;
};

inline Matrix33::Matrix33
(
)
{
}

inline Matrix33::Matrix33
(
	Vector3ConstRef _c1, 
	Vector3ConstRef _c2, 
	Vector3ConstRef _c3
)
{
	m_c1 = _c1.m_value;
	m_c2 = _c2.m_value;
	m_c3 = _c3.m_value;
};

inline Matrix33::Matrix33
(
	Matrix33ConstRef _other
)
{
	m_c1 = _other.m_c1;
	m_c2 = _other.m_c2;
	m_c3 = _other.m_c3;
};

inline Matrix33Ref Matrix33::operator=
(
	Matrix33ConstRef _other
)
{
	m_c1 = _other.m_c1;
	m_c2 = _other.m_c2;
	m_c3 = _other.m_c3;
	return *this;
}

inline Vector3 Matrix33::GetColumn1
(
) const
{
	return Vector3(m_c1);
}
inline Vector3 Matrix33::GetColumn2
(
) const
{
	return Vector3(m_c2);
}
inline Vector3 Matrix33::GetColumn3
(
) const
{
	return Vector3(m_c3);
}

inline void Matrix33::SetColumn1
(
	Vector3ConstRef _c1
)
{
	m_c1 = _c1.m_value;
}
inline void Matrix33::SetColumn2
(
	Vector3ConstRef _c2
)
{
	m_c2 = _c2.m_value;
}
inline void Matrix33::SetColumn3
(
	Vector3ConstRef _c3
)
{
	m_c3 = _c3.m_value;
}


inline Matrix33 operator+
(
	Matrix33ConstRef _l, 
	Matrix33ConstRef _r
)
{
	Matrix33 ret;
	ret.m_c1 = _mm_add_ps(_l.m_c1, _r.m_c2);
	ret.m_c2 = _mm_add_ps(_l.m_c2, _r.m_c2);
	ret.m_c3 = _mm_add_ps(_l.m_c3, _r.m_c3);

	return ret;
}
inline Matrix33 operator-
(
	Matrix33ConstRef _l, 
	Matrix33ConstRef _r
)
{
	Matrix33 ret;
	ret.m_c1 = _mm_sub_ps(_l.m_c1, _r.m_c2);
	ret.m_c2 = _mm_sub_ps(_l.m_c2, _r.m_c2);
	ret.m_c3 = _mm_sub_ps(_l.m_c3, _r.m_c3);

	return ret;
}
inline Matrix33 operator*
(
	Matrix33ConstRef _l, 
	Matrix33ConstRef _r
)
{
	/*
	
	U11	U12	U13		V11	V12	V13
	U21	U22	U23		V21	V22	V23	
	U31	U32	U33		V31	V32	V33	

	O11 = U11*V11 + U12*V21 + U12*V31
	O21 = U21*V11 + U22*V21 + U22*V31
	O31 = U31*V11 + U32*V21 + U32*V31
	
	*/
	__m128 c11 = _mm_mul_ps( _l.m_c1, _mm_shuffle_ps(_r.m_c1, _r.m_c1, _MM_SHUFFLE(0, 0, 0, 0)));
	__m128 c12 = _mm_mul_ps( _l.m_c2, _mm_shuffle_ps(_r.m_c1, _r.m_c1, _MM_SHUFFLE(1, 1, 1, 1)));
	__m128 c13 = _mm_mul_ps( _l.m_c3, _mm_shuffle_ps(_r.m_c1, _r.m_c1, _MM_SHUFFLE(2, 2, 2, 2)));

	__m128 c1 = _mm_add_ps(c11, _mm_add_ps(c12, c13));
	
	__m128 c21 = _mm_mul_ps( _l.m_c1, _mm_shuffle_ps(_r.m_c2, _r.m_c2, _MM_SHUFFLE(0, 0, 0, 0)));
	__m128 c22 = _mm_mul_ps( _l.m_c2, _mm_shuffle_ps(_r.m_c2, _r.m_c2, _MM_SHUFFLE(1, 1, 1, 1)));
	__m128 c23 = _mm_mul_ps( _l.m_c3, _mm_shuffle_ps(_r.m_c2, _r.m_c2, _MM_SHUFFLE(2, 2, 2, 2)));
			
	__m128 c2 = _mm_add_ps(c21, _mm_add_ps(c22, c23));
	
	__m128 c31 = _mm_mul_ps( _l.m_c1, _mm_shuffle_ps(_r.m_c3, _r.m_c3, _MM_SHUFFLE(0, 0, 0, 0)));
	__m128 c32 = _mm_mul_ps( _l.m_c2, _mm_shuffle_ps(_r.m_c3, _r.m_c3, _MM_SHUFFLE(1, 1, 1, 1)));
	__m128 c33 = _mm_mul_ps( _l.m_c3, _mm_shuffle_ps(_r.m_c3, _r.m_c3, _MM_SHUFFLE(2, 2, 2, 2)));
			
	__m128 c3 = _mm_add_ps(c31, _mm_add_ps(c32, c33));

	return Matrix33
	(
		Vector3(c1),
		Vector3(c2),
		Vector3(c3)
	);
}

inline Vector3 operator*
(
	Matrix33ConstRef _l, 
	Vector3ConstRef _r
)
{
	/*
	
	m11	m12	m13		v1
	m21	m22	m23		v2
	m31	m32	m33		v3

	vO1 = m11*v1 + m12*v2 + m13*v3
	vO2 = m21*v1 + m22*v2 + m23*v3
	vO3 = m31*v1 + m32*v2 + m33*v3
	
	*/

	__m128 c1 = _mm_mul_ps( _l.m_c1, _mm_shuffle_ps(_r.m_value, _r.m_value, _MM_SHUFFLE(0, 0, 0, 0)));
	__m128 c2 = _mm_mul_ps( _l.m_c2, _mm_shuffle_ps(_r.m_value, _r.m_value, _MM_SHUFFLE(1, 1, 1, 1)));
	__m128 c3 = _mm_mul_ps( _l.m_c3, _mm_shuffle_ps(_r.m_value, _r.m_value, _MM_SHUFFLE(2, 2, 2, 2)));

	return Vector3
	(
		_mm_add_ps(c1, _mm_add_ps(c2, c3))
	);
}

inline bool operator==
(
	Matrix33ConstRef _l, 
	Matrix33ConstRef _r
)
{
	__m128 r1Result = _mm_cmpeq_ss(_l.m_c1, _r.m_c1);
	__m128 r2Result = _mm_cmpeq_ss(_l.m_c2, _r.m_c2);
	__m128 r3Result = _mm_cmpeq_ss(_l.m_c3, _r.m_c3);

	__m128 result = _mm_and_ps(r1Result, _mm_and_ps(r2Result, r3Result));
	
	__declspec(align(16)) uint32 storedBits[4];
	_mm_store_ps( (float*)storedBits, result );
	return storedBits[0] == 0xffffffff && storedBits[1] == 0xffffffff && storedBits[2] == 0xffffffff;
}
inline bool operator!=
(
	Matrix33ConstRef _l, 
	Matrix33ConstRef _r
)
{	
	__m128 r1Result = _mm_cmpneq_ss(_l.m_c1, _r.m_c1);
	__m128 r2Result = _mm_cmpneq_ss(_l.m_c2, _r.m_c2);
	__m128 r3Result = _mm_cmpneq_ss(_l.m_c3, _r.m_c3);

	__m128 result = _mm_and_ps(r1Result, _mm_and_ps(r2Result, r3Result));
	
	__declspec(align(16)) uint32 storedBits[4];
	_mm_store_ps( (float*)storedBits, result );
	return storedBits[0] == 0xffffffff && storedBits[1] == 0xffffffff && storedBits[2] == 0xffffffff;
}

inline Matrix33 Transpose
(
	Matrix33ConstRef _param
)
{
	// from _MM_TRANSPOSE4_PS                       

	static __m128 const c4 = _mm_set_ps(0.f, 0.f, 0.f, 0.f);

	__m128 tmp0 = _mm_shuffle_ps(_param.m_c1, _param.m_c2,	0x44);//tmp0 = (c0x, c0y, c1x, c1y)
	__m128 tmp1 = _mm_shuffle_ps(_param.m_c3, c4,			0x44);//tmp1 = (c2x, c2y, 0, 0)
	__m128 tmp2 = _mm_shuffle_ps(_param.m_c1, _param.m_c2,	0xEE);//tmp2 = (c0z, 0, c1z, 0)
	__m128 tmp3 = _mm_shuffle_ps(_param.m_c3, c4,			0xEE);//tmp3 = (c2z, c2w, 0, 0)

	Matrix33 ret;
	ret.m_c1 = _mm_shuffle_ps(tmp0, tmp1, 0x88);//col0 = (c0x, c1x, c2x, c3x)
	ret.m_c2 = _mm_shuffle_ps(tmp0, tmp1, 0xDD);
	ret.m_c3 = _mm_shuffle_ps(tmp2, tmp3, 0x88);

	return ret;
}