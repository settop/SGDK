#pragma once

#include "Vector.h"
#include "Vector1.h"
#include "Vector2.h"

__declspec(align(16)) class Vector3
{
public:
	typedef Vector3 const Vector3ConstParam;
	typedef Vector3 const& Vector3ConstRef;
	typedef Vector3& Vector3Ref;
public:
	template<int I>
	static Vector3 Integer();
	template<int I1, int I2, int I3>
	static Vector3 Integer();

	template<int N, int D>
	static Vector3 Fraction();
	template<int N1, int D1, int N2, int D2, int N3, int D3>
	static Vector3 Fraction();

	static Vector3 Zero();
	static Vector3 One();
	static Vector3 Two();
	static Vector3 MinusOne();
	static Vector3 Half();
	static Vector3 Quarter();
	static Vector3 Pi();
	static Vector3 TwoPi();
	static Vector3 PiBy2();
	static Vector3 PiBy4();

	inline Vector3();
	inline Vector3(Vector1ConstRef _x, Vector1ConstRef _y, Vector1ConstRef _z);
	inline Vector3(Vector2ConstRef _xy, Vector1ConstRef _z);
	inline Vector3(Vector3ConstRef _other);

	inline Vector3Ref operator=(Vector3ConstRef _other);

	inline Vector1 GetX() const;
	inline Vector1 GetY() const;
	inline Vector1 GetZ() const;
	inline Vector1 X() const { return GetX(); }
	inline Vector1 Y() const { return GetY(); }
	inline Vector1 Z() const { return GetZ(); }

	inline void SetX(Vector1ConstRef _x);
	inline void SetY(Vector1ConstRef _y);
	inline void SetZ(Vector1ConstRef _z);

	inline Vector3(__m128 _value);

	__m128 m_value;
};

inline Vector3 LoadVector3(float *_value);
inline void StoreVector3(Vector3ConstRef _vector, float *_value);

inline Vector3 operator+(Vector3ConstRef _l, Vector3ConstRef _r);
inline Vector3 operator-(Vector3ConstRef _l, Vector3ConstRef _r);
inline Vector3 operator*(Vector3ConstRef _l, Vector1ConstRef _r);
inline Vector3 operator*(Vector1ConstRef _l, Vector3ConstRef _r);
inline Vector3 operator/(Vector3ConstRef _l, Vector1ConstRef _r);

inline bool operator==(Vector3ConstRef _l, Vector3ConstRef _r);
inline bool operator!=(Vector3ConstRef _l, Vector3ConstRef _r);

inline Vector1 Dot(Vector3ConstRef _l, Vector3ConstRef _r);
inline Vector1 Length(Vector3ConstRef _param);
inline Vector3 Cross(Vector3ConstRef _l, Vector3ConstRef _r);
inline Vector3 Abs(Vector3ConstRef _param);
inline Vector3 Sqrt(Vector3ConstRef _param);
inline Vector3 Reciprocal(Vector3ConstRef _param);
inline Vector3 ReciprocalSqrt(Vector3ConstRef _param);
inline Vector3 Min(Vector3ConstRef _a, Vector3ConstRef _b);
inline Vector3 Max(Vector3ConstRef _a, Vector3ConstRef _b);
inline Vector3 And(Vector3ConstRef _a, Vector3ConstRef _b);
inline Vector3 Or(Vector3ConstRef _a, Vector3ConstRef _b);
inline Vector3 Xor(Vector3ConstRef _a, Vector3ConstRef _b);

#include "Vector3.inl"