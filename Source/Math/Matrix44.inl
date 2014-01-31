#pragma once

#include "Matrix44.h"

template<int I>
Matrix44 Matrix44::Integer
(
)
{
	static Matrix44 result = Matrix44(Vector4::Integer<I, 0, 0, 0>(), Vector4::Integer<0, I, 0, 0>(), Vector4::Integer<0, 0, I, 0>(), Vector4::Integer<0, 0, 0, I>());
	return result;
};
Matrix44 Matrix44::Identity
(
)
{
	static Matrix44 result = Matrix44(Vector4::Integer<1, 0, 0, 0>(), Vector4::Integer<0, 1, 0, 0>(), Vector4::Integer<0, 0, 1, 0>(), Vector4::Integer<0, 0, 0, 1>());
	return result;
};
Matrix44 Matrix44::Zero
(
)
{
	static Matrix44 result = Matrix44(Vector4::Zero(), Vector4::Zero(), Vector4::Zero(), Vector4::Zero());
	return result;
};

inline Matrix44::Matrix44
(
)
{
}

inline Matrix44::Matrix44
(
	Vector4ConstRef _c1, 
	Vector4ConstRef _c2, 
	Vector4ConstRef _c3, 
	Vector4ConstRef _c4
)
{
	m_c1 = _c1.m_value;
	m_c2 = _c2.m_value;
	m_c3 = _c3.m_value;
	m_c4 = _c4.m_value;
};

inline Matrix44::Matrix44
(
	Matrix44ConstRef _other
)
{
	m_c1 = _other.m_c1;
	m_c2 = _other.m_c2;
	m_c3 = _other.m_c3;
	m_c4 = _other.m_c4;
};

inline Matrix44Ref Matrix44::operator=
(
	Matrix44ConstRef _other
)
{
	m_c1 = _other.m_c1;
	m_c2 = _other.m_c2;
	m_c3 = _other.m_c3;
	m_c4 = _other.m_c4;
	return *this;
}

inline Vector4 Matrix44::GetColumn1
(
) const
{
	return Vector4(m_c1);
}
inline Vector4 Matrix44::GetColumn2
(
) const
{
	return Vector4(m_c2);
}
inline Vector4 Matrix44::GetColumn3
(
) const
{
	return Vector4(m_c3);
}
inline Vector4 Matrix44::GetColumn4
(
) const
{
	return Vector4(m_c4);
}

inline void Matrix44::SetColumn1
(
	Vector4ConstRef _c1
)
{
	m_c1 = _c1.m_value;
}
inline void Matrix44::SetColumn2
(
	Vector4ConstRef _c2
)
{
	m_c2 = _c2.m_value;
}
inline void Matrix44::SetColumn3
(
	Vector4ConstRef _c3
)
{
	m_c3 = _c3.m_value;
}
inline void Matrix44::SetColumn4
(
	Vector4ConstRef _c4
)
{
	m_c4 = _c4.m_value;
}


inline Matrix44 operator+
(
	Matrix44ConstRef _l, 
	Matrix44ConstRef _r
)
{
	Matrix44 ret;
	ret.m_c1 = _mm_add_ps(_l.m_c1, _r.m_c2);
	ret.m_c2 = _mm_add_ps(_l.m_c2, _r.m_c2);
	ret.m_c3 = _mm_add_ps(_l.m_c3, _r.m_c3);
	ret.m_c4 = _mm_add_ps(_l.m_c4, _r.m_c4);

	return ret;
}
inline Matrix44 operator-
(
	Matrix44ConstRef _l, 
	Matrix44ConstRef _r
)
{
	Matrix44 ret;
	ret.m_c1 = _mm_sub_ps(_l.m_c1, _r.m_c2);
	ret.m_c2 = _mm_sub_ps(_l.m_c2, _r.m_c2);
	ret.m_c3 = _mm_sub_ps(_l.m_c3, _r.m_c3);
	ret.m_c4 = _mm_sub_ps(_l.m_c4, _r.m_c4);

	return ret;
}
inline Matrix44 operator*
(
	Matrix44ConstRef _l, 
	Matrix44ConstRef _r
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
	__m128 c14 = _mm_mul_ps( _l.m_c4, _mm_shuffle_ps(_r.m_c1, _r.m_c1, _MM_SHUFFLE(3, 3, 3, 3)));

	__m128 c1 = _mm_add_ps(_mm_add_ps(c11, c12), _mm_add_ps(c13, c14));
	
	__m128 c21 = _mm_mul_ps( _l.m_c1, _mm_shuffle_ps(_r.m_c2, _r.m_c2, _MM_SHUFFLE(0, 0, 0, 0)));
	__m128 c22 = _mm_mul_ps( _l.m_c2, _mm_shuffle_ps(_r.m_c2, _r.m_c2, _MM_SHUFFLE(1, 1, 1, 1)));
	__m128 c23 = _mm_mul_ps( _l.m_c3, _mm_shuffle_ps(_r.m_c2, _r.m_c2, _MM_SHUFFLE(2, 2, 2, 2)));
	__m128 c24 = _mm_mul_ps( _l.m_c4, _mm_shuffle_ps(_r.m_c2, _r.m_c2, _MM_SHUFFLE(3, 3, 3, 3)));
			
	__m128 c2 = _mm_add_ps(_mm_add_ps(c21, c22), _mm_add_ps(c23, c24));
	
	__m128 c31 = _mm_mul_ps( _l.m_c1, _mm_shuffle_ps(_r.m_c3, _r.m_c3, _MM_SHUFFLE(0, 0, 0, 0)));
	__m128 c32 = _mm_mul_ps( _l.m_c2, _mm_shuffle_ps(_r.m_c3, _r.m_c3, _MM_SHUFFLE(1, 1, 1, 1)));
	__m128 c33 = _mm_mul_ps( _l.m_c3, _mm_shuffle_ps(_r.m_c3, _r.m_c3, _MM_SHUFFLE(2, 2, 2, 2)));
	__m128 c34 = _mm_mul_ps( _l.m_c4, _mm_shuffle_ps(_r.m_c3, _r.m_c3, _MM_SHUFFLE(2, 2, 2, 2)));
			
	__m128 c3 = _mm_add_ps(_mm_add_ps(c31, c32), _mm_add_ps(c33, c34));
	
	__m128 c41 = _mm_mul_ps( _l.m_c1, _mm_shuffle_ps(_r.m_c4, _r.m_c4, _MM_SHUFFLE(0, 0, 0, 0)));
	__m128 c42 = _mm_mul_ps( _l.m_c2, _mm_shuffle_ps(_r.m_c4, _r.m_c4, _MM_SHUFFLE(1, 1, 1, 1)));
	__m128 c43 = _mm_mul_ps( _l.m_c3, _mm_shuffle_ps(_r.m_c4, _r.m_c4, _MM_SHUFFLE(2, 2, 2, 2)));
	__m128 c44 = _mm_mul_ps( _l.m_c4, _mm_shuffle_ps(_r.m_c4, _r.m_c4, _MM_SHUFFLE(2, 2, 2, 2)));
			
	__m128 c4 = _mm_add_ps(_mm_add_ps(c41, c42), _mm_add_ps(c43, c44));

	return Matrix44
	(
		Vector4(c1),
		Vector4(c2),
		Vector4(c3),
		Vector4(c4)
	);
}

inline Vector3 operator*
(
	Matrix44ConstRef _l, 
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
	__m128 c4 = _mm_mul_ps( _l.m_c4, _mm_shuffle_ps(_r.m_value, _r.m_value, _MM_SHUFFLE(3, 3, 3, 3)));

	return Vector3
	(
		_mm_add_ps(_mm_add_ps(c1, c2), _mm_add_ps(c3, c4))
	);
}

inline bool operator==
(
	Matrix44ConstRef _l, 
	Matrix44ConstRef _r
)
{
	__m128 r1Result = _mm_cmpeq_ss(_l.m_c1, _r.m_c1);
	__m128 r2Result = _mm_cmpeq_ss(_l.m_c2, _r.m_c2);
	__m128 r3Result = _mm_cmpeq_ss(_l.m_c3, _r.m_c3);
	__m128 r4Result = _mm_cmpeq_ss(_l.m_c4, _r.m_c4);

	__m128 result = _mm_and_ps(_mm_and_ps(r1Result, r2Result), _mm_and_ps(r3Result, r4Result));
	
	__declspec(align(16)) uint32 storedBits[4];
	_mm_store_ps( (float*)storedBits, result );
	return storedBits[0] == 0xffffffff && storedBits[1] == 0xffffffff && storedBits[2] == 0xffffffff && storedBits[3] == 0xffffffff;
}
inline bool operator!=
(
	Matrix44ConstRef _l, 
	Matrix44ConstRef _r
)
{	
	__m128 r1Result = _mm_cmpneq_ss(_l.m_c1, _r.m_c1);
	__m128 r2Result = _mm_cmpneq_ss(_l.m_c2, _r.m_c2);
	__m128 r3Result = _mm_cmpneq_ss(_l.m_c3, _r.m_c3);
	__m128 r4Result = _mm_cmpneq_ss(_l.m_c4, _r.m_c4);
	
	__m128 result = _mm_and_ps(_mm_and_ps(r1Result, r2Result), _mm_and_ps(r3Result, r4Result));
	
	__declspec(align(16)) uint32 storedBits[4];
	_mm_store_ps( (float*)storedBits, result );
	return storedBits[0] == 0xffffffff && storedBits[1] == 0xffffffff && storedBits[2] == 0xffffffff && storedBits[3] == 0xffffffff;
}

inline Matrix44 Transpose
(
	Matrix44ConstRef _param
)
{
	// from _MM_TRANSPOSE4_PS

	__m128 tmp0 = _mm_shuffle_ps(_param.m_c1, _param.m_c2,	0x44);//tmp0 = (c0x, c0y, c1x, c1y)
	__m128 tmp1 = _mm_shuffle_ps(_param.m_c3, _param.m_c4,	0x44);//tmp1 = (c2x, c2y, 0, 0)
	__m128 tmp2 = _mm_shuffle_ps(_param.m_c1, _param.m_c2,	0xEE);//tmp2 = (c0z, 0, c1z, 0)
	__m128 tmp3 = _mm_shuffle_ps(_param.m_c3, _param.m_c4,	0xEE);//tmp3 = (c2z, c2w, 0, 0)

	Matrix44 ret;
	ret.m_c1 = _mm_shuffle_ps(tmp0, tmp1, 0x88);//col0 = (c0x, c1x, c2x, c3x)
	ret.m_c2 = _mm_shuffle_ps(tmp0, tmp1, 0xDD);
	ret.m_c3 = _mm_shuffle_ps(tmp2, tmp3, 0x88);
	ret.m_c4 = _mm_shuffle_ps(tmp2, tmp3, 0xDD);

	return ret;
}