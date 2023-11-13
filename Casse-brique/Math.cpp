#include "Math.h"
#include<cmath>


void Math::normalize(float* x, float* y)
{
	float xtmp = *x;
	*x /= sqrt(xtmp * xtmp + *y * *y);
	*y /= sqrt(xtmp * xtmp + *y * *y);
}

float Math::min(float x, float y)
{
	if (x < y)
		return x;
	else
		return y;
}

float Math::abs(float x)
{
	return std::abs(x);
}