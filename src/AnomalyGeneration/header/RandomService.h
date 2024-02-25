#ifndef RandomService_h
#define RandomService_h

#include <math.h>
#include <cstdlib>
#include "corecrt_math_defines.h"

class RandomService {

public:
	int random(int steuerung, double pixelDistribution);
	double randomOneScaled();
};

#endif