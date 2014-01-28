#pragma once

#include "Vector.h"
#include "Vector1.h"

__declspec(align(16)) class Vector2
{
public:
	typedef Vector2 const Vector2ConstParam;
	typedef Vector2 const& Vector2ConstRef;
	typedef Vector2& Vector2Ref;
public:
	template<int I>
	static Vector2 Integer();
	template<int I1, int I2>
	static Vector2 Integer();

	template<int N, int D>
	static Vector2 Fraction();
	template<int N1, int D1, int N2, int D2>
	static Vector2 Fraction();

	static Vector2 Zero();
	static Vector2 One();
	static Vector2 Two();
	static Vector2 MinusOne();
	static Vector2 Half();
	static Vector2 Quarter();
	static Vector2 Pi();
	static Vector2 TwoPi();
	static Vector2 PiBy2();
	static Vector2 PiBy4();

	inline Vector2();
	inline Vector2(Vector1ConstRef _x, Vector1ConstRef _y);
	inline Vector2(Vector2ConstRef _other);

	inline Vector2Ref operator=(Vector2ConstRef _other);

	inline Vector1 GetX() const;
	inline Vector1 GetY() const;
	inline Vector1 X() const { return GetX(); }
	inline Vector1 Y() const { return GetY(); }

	inline void SetX(Vector1ConstRef _x);
	inline void SetY(Vector1ConstRef _y);

	inline Vector2(__m128 _value);

	__m128 m_value;
};

inline Vector2 LoadVector2(float *_value);
inline void StoreVector2(Vector2ConstRef _vector, float *_value);

inline Vector2 operator+(Vector2ConstRef _l, Vector2ConstRef _r);
inline Vector2 operator-(Vector2ConstRef _l, Vector2ConstRef _r);
inline Vector2 operator*(Vector2ConstRef _l, Vector1ConstRef _r);
inline Vector2 operator*(Vector1ConstRef _l, Vector2ConstRef _r);
inline Vector2 operator/(Vector2ConstRef _l, Vector1ConstRef _r);

inline bool operator==(Vector2ConstRef _l, Vector2ConstRef _r);
inline bool operator!=(Vector2ConstRef _l, Vector2ConstRef _r);

inline Vector1 Dot(Vector2ConstRef _l, Vector2ConstRef _r);
inline Vector1 Length(Vector2ConstRef _param);
inline Vector2 Abs(Vector2ConstRef _param);
inline Vector2 Sqrt(Vector2ConstRef _param);
inline Vector2 Reciprocal(Vector2ConstRef _param);
inline Vector2 ReciprocalSqrt(Vector2ConstRef _param);
inline Vector2 Min(Vector2ConstRef _a, Vector2ConstRef _b);
inline Vector2 Max(Vector2ConstRef _a, Vector2ConstRef _b);
inline Vector2 And(Vector2ConstRef _a, Vector2ConstRef _b);
inline Vector2 Or(Vector2ConstRef _a, Vector2ConstRef _b);
inline Vector2 Xor(Vector2ConstRef _a, Vector2ConstRef _b);

#include "Vector2.inl"