#pragma once

#include "Vector.h"

__declspec(align(16)) class Vector1
{
public:
	typedef Vector1 const Vector1ConstParam;
	typedef Vector1 const& Vector1ConstRef;
	typedef Vector1& Vector1Ref;
public:
	template<int I>
	static Vector1 Integer();
	template<int N, int D>
	static Vector1 Fraction();
	static Vector1 Zero();
	static Vector1 One();
	static Vector1 Two();
	static Vector1 MinusOne();
	static Vector1 Half();
	static Vector1 Quarter();
	static Vector1 Pi();
	static Vector1 TwoPi();
	static Vector1 PiBy2();
	static Vector1 PiBy4();

	inline Vector1();
	inline Vector1(Vector1ConstRef _other);

	inline Vector1Ref operator=(Vector1ConstRef _other);

	inline Vector1(__m128 _value);

	__m128 m_value;
};

inline Vector1 LoadVector1(float *_value);
inline void StoreVector1(Vector1ConstRef _vector, float *_value);

inline Vector1 operator+(Vector1ConstRef _l, Vector1ConstRef _r);
inline Vector1 operator-(Vector1ConstRef _l, Vector1ConstRef _r);
inline Vector1 operator*(Vector1ConstRef _l, Vector1ConstRef _r);
inline Vector1 operator/(Vector1ConstRef _l, Vector1ConstRef _r);

inline bool operator==(Vector1ConstRef _l, Vector1ConstRef _r);
inline bool operator!=(Vector1ConstRef _l, Vector1ConstRef _r);
inline bool operator>(Vector1ConstRef _l, Vector1ConstRef _r);
inline bool operator>=(Vector1ConstRef _l, Vector1ConstRef _r);
inline bool operator<(Vector1ConstRef _l, Vector1ConstRef _r);
inline bool operator<=(Vector1ConstRef _l, Vector1ConstRef _r);

inline Vector1 Dot(Vector1ConstRef _l, Vector1ConstRef _r);
inline Vector1 Length(Vector1ConstRef _param);
inline Vector1 Abs(Vector1ConstRef _param);
inline Vector1 Sqrt(Vector1ConstRef _param);
inline Vector1 Reciprocal(Vector1ConstRef _param);
inline Vector1 ReciprocalSqrt(Vector1ConstRef _param);
inline Vector1 Min(Vector1ConstRef _a, Vector1ConstRef _b);
inline Vector1 Max(Vector1ConstRef _a, Vector1ConstRef _b);
inline Vector1 Lerp(Vector1ConstRef _a, Vector1ConstRef _b, Vector1ConstRef _lerpValue);
inline Vector1 And(Vector1ConstRef _a, Vector1ConstRef _b);
inline Vector1 Or(Vector1ConstRef _a, Vector1ConstRef _b);
inline Vector1 Xor(Vector1ConstRef _a, Vector1ConstRef _b);


#include "Vector1.inl"