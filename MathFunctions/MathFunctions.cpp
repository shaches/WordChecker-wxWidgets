#include "MathFunctions.h"

namespace mathfunctions
{
	double sqrt(double value)
	{
		#ifdef USE_MYMATH
		return mysqrt(value);
		#else
		return std::sqrt(value);
		#endif
	}
}
