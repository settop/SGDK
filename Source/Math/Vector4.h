#pragma once

#include "Vector.h"
#include "Vector1.h"
#include "Vector2.h"
#include "Vector3.h"

__declspec(align(16)) class Vector4
{
public:
	typedef Vector4 const Vector4ConstParam;
	typedef Vector4 const& Vector4ConstRef;
	typedef Vector4& Vector4Ref;
public:
	template<int I>
	static Vector4 Integer();
	template<int I1, int I2, int I3, int I4>
	static Vector4 Integer();

	template<int N, int D>
	static Vector4 Fraction();
	template<int N1, int D1, int N2, int D2, int N3, int D3, int N4, int D4>
	static Vector4 Fraction();

	static Vector4 Zero();
	static Vector4 One();
	static Vector4 Two();
	static Vector4 MinusOne();
	static Vector4 Half();
	static Vector4 Quarter();
	static Vector4 Pi();
	static Vector4 TwoPi();
	static Vector4 PiBy2();
	static Vector4 PiBy4();

	inline Vector4();
	inline Vector4(Vector1ConstRef _x, Vector1ConstRef _y, Vector1ConstRef _z, Vector1ConstRef _w);
	inline Vector4(Vector2ConstRef _xy, Vector1ConstRef _z, Vector1ConstRef _w);
	inline Vector4(Vector3ConstRef _xyz, Vector1ConstRef _w);
	inline Vector4(Vector4ConstRef _other);

	inline Vector4Ref operator=(Vector4ConstRef _other);

	inline Vector1 GetX() const;
	inline Vector1 GetY() const;
	inline Vector1 GetZ() const;
	inline Vector1 GetW() const;
	inline Vector1 X() const { return GetX(); }
	inline Vector1 Y() const { return GetY(); }
	inline Vector1 Z() const { return GetZ(); }
	inline Vector1 W() const { return GetW(); }

	inline void SetX(Vector1ConstRef _x);
	inline void SetY(Vector1ConstRef _y);
	inline void SetZ(Vector1ConstRef _z);
	inline void SetW(Vector1ConstRef _w);

	inline Vector4(__m128 _value);

	__m128 m_value;
};

inline Vector4 LoadVector4(float *_value);
inline void StoreVector4(Vector4ConstRef _vector, float *_value);

inline Vector4 operator+(Vector4ConstRef _l, Vector4ConstRef _r);
inline Vector4 operator-(Vector4ConstRef _l, Vector4ConstRef _r);
inline Vector4 operator*(Vector4ConstRef _l, Vector1ConstRef _r);
inline Vector4 operator*(Vector1ConstRef _l, Vector4ConstRef _r);
inline Vector4 operator/(Vector4ConstRef _l, Vector1ConstRef _r);

inline bool operator==(Vector4ConstRef _l, Vector4ConstRef _r);
inline bool operator!=(Vector4ConstRef _l, Vector4ConstRef _r);

inline Vector1 Dot(Vector4ConstRef _l, Vector4ConstRef _r);
inline Vector1 Length(Vector4ConstRef _param);
inline Vector4 Abs(Vector4ConstRef _param);
inline Vector4 Sqrt(Vector4ConstRef _param);
inline Vector4 Reciprocal(Vector4ConstRef _param);
inline Vector4 ReciprocalSqrt(Vector4ConstRef _param);
inline Vector4 Min(Vector4ConstRef _a, Vector4ConstRef _b);
inline Vector4 Max(Vector4ConstRef _a, Vector4ConstRef _b);
inline Vector4 And(Vector4ConstRef _a, Vector4ConstRef _b);
inline Vector4 Or(Vector4ConstRef _a, Vector4ConstRef _b);
inline Vector4 Xor(Vector4ConstRef _a, Vector4ConstRef _b);

#include "Vector4.inl"