#include "Math.h"
#include<math.h>

void Math::normalize(float* x, float* y)
{
	*x /= sqrt(*x * *x + *y * *y);
	*y /= sqrt(*x * *x + *y * *y);
}
