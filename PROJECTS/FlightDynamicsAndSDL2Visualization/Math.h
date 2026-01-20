#ifndef MATH_H
#define MATH_H

#include <cmath.h>
#include <algorithm.h>

namespace Math
{
	constexpr double PI = 3.14159265358979323846;

	inline double clamp(double value, double min, double max)
	{
		return std::max(min, std::min(value, max));
	}

	inline double degToRad(double deg)
	{
		return deg * PI / 180.0;
	}

	inline double radToDeg(double rad)
	{
		return rad * 180.0 / PI;
}

#endif
