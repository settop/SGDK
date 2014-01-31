#pragma once

#include "Math.h"

template<typename T> 
inline T Min
(
	T const &_a, 
	T const &_b
)
{
	return _a < _b ? _a : _b;
};

template<typename T> 
inline T Max
(
	T const &_a, 
	T const &_b
)
{
	return _a > _b ? _a : _b;
};

template<typename T> 
inline T Clamp
(
	T const &_v, 
	T const &_min, 
	T const &_max
)
{
	return Max(_min, Min(_v, _max));
};

template<typename T> 
inline T Lerp
(
	T const &_a, 
	T const &_b, 
	float _lerpValue
)
{
	return _a * (1.f - _lerpValue) + _b * (_lerpValue);
}

template<typename T> 
inline T Lerp
(
	T const &_a, 
	T const &_b, 
	double _lerpValue
)
{
	return _a * (1.0 - _lerpValue) + _b * (_lerpValue);
}