#include "Math.h"
#include<math.h>

void Math::normalize(float* x, float* y)
{
	float xtmp = *x;
	*x /= sqrt(xtmp * xtmp + *y * *y);
	*y /= sqrt(xtmp * xtmp + *y * *y);
}