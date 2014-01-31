#pragma once

#include "Vector.h"
#include "Constants.h"
#include "Vector1.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Matrix33.h"
#include "Matrix44.h"

//returns the minimum of _a and _b
template<typename T> inline T Min(T const &_a, T const &_b);
//returns the maximum of _a and _b
template<typename T> inline T Max(T const &_a, T const &_b);
//returns _v clamped to be within _min to _max
template<typename T> inline T Clamp(T const &_v, T const &_min, T const &_max);

//returns the linear interpoloation of _a to _b by _lerpValue
template<typename T> inline T Lerp(T const &_a, T const &_b, float _lerpValue);
//returns the linear interpoloation of _a to _b by _lerpValue
template<typename T> inline T Lerp(T const &_a, T const &_b, double _lerpValue);

#include "Math.inl"