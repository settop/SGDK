#pragma once

#include "Quaternion.h"

Quaternion Quaternion::Identity
(
)
{
	static Quaternion const result = Quaternion(_mm_set_ps(0.f, 0.f, 0.f, 1.f));
	return result;
}

Quaternion::Quaternion
(
)
{
}

Quaternion::Quaternion
(
	Vector3 _axis, 
	Vector1 _angle
)
{
	Assert(IsNormalised(_axis));
	Vector1 halfAngle = _angle * Vector1::Half();

	Vector1 cosHalfAngle = Cos(halfAngle);
	Vector1 sinHalfAngle = Sin(halfAngle);

	m_value = _mm_add_ps((_axis * sinHalfAngle).m_value , _mm_and_ps(cosHalfAngle.m_value, VectorMasks::WMask));
}

Quaternion::Quaternion
(
	__m128 _value
) : m_value(_value)
{
}

inline Quaternion operator*
(
	QuaternionConstRef _l, 
	QuaternionConstRef _r
)
{
	//(a + bi + cj + dk) (e + fi + gj + hk) =
	//(ae - bf - cg - dh) + (af + be + ch - dg)i + (ag - bh + ce + df) j + (ah + bg - cf + de) k.
}

inline Quaternion Invert(QuaternionConstRef _param);
inline Quaternion Conjugate(QuaternionConstRef _param);