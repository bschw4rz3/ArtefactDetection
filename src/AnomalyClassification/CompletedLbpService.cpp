#include "CompletedLbpService.h"

int CompletedLbpService::functionS(double value)
{	
	double sp = sign(value);
	double mp = abs(value);

	double dp = sp * mp;

	return dp >= 0 ? 1 : -1;
}

double CompletedLbpService::sign(double x)
{
	if (x > 0) return 1;
	if (x < 0) return -1;
	return 0;
}