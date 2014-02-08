#pragma once

#include "Vector.h"
#include "Vector3.h"

__declspec(align(16)) class Quaternion
{
public:
	typedef Quaternion const QuaternionConstParam;
	typedef Quaternion const& QuaternionConstRef;
	typedef Quaternion& QuaternionRef;
public:
	static Quaternion Identity();

	Quaternion();
	Quaternion(Vector3 _axis, Vector1 _angle);

	Quaternion(__m128 _value);
	__m128 m_value;
};

inline Quaternion operator*(QuaternionConstRef _l, QuaternionConstRef _r);

inline Quaternion Invert(QuaternionConstRef _param);
inline Quaternion Conjugate(QuaternionConstRef _param);

#include "Quaternion.inl"