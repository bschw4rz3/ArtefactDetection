#ifndef Math_H
#define Math_H

#include <math.h>

# define M_PI           3.14159265358979323846  /* pi */


class MathSerivce
{
public:
	double degreesToRadians(double degreeAngel);
	double radiansToDegrees(double radiant);

	double sinDegrees(double deg);
	double atanDegrees(double value);

	double roundDigits(double value, int digit);

};

#endif