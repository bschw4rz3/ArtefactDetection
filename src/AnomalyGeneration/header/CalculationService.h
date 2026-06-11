#ifndef CalculationService_H
#define CalculationService_H

#include <math.h>
#include "corecrt_math_defines.h"

#include "PixelPosition.h"

class CalculationService 
{
public:
	PixelPosition rotation(PixelPosition position, double degree);

	double toRadiant(double degree);
};

#endif