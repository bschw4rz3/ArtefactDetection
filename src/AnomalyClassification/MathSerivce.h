#ifndef Math_H
#define Math_H

#include <math.h>
#include <complex>
#include <vector>

#define M_PI            3.14159265358979323846  /* pi */
#define M_E				2.71828182845904523536


class MathSerivce
{
public:
	double degreesToRadians(double degreeAngel);
	double radiansToDegrees(double radiant);

	double sinDegrees(double degreeAngel);
	double cosDegrees(double degreeAngel);
	double atanDegrees(double value);

	double roundDigits(double value, int digit);
	double calculateEuler(std::complex<double> time, double w_0);

	long double avg(std::vector<double> v);
	long double calculateSkewness(std::vector<double> data);
	long double calculateStandardDeviation(const std::vector<double>& data, double mean);
	long double calculateVariance(const std::vector<double> data);
	long double calculateEnergy(const std::vector<double>& signal);
	long double calculateKurtosis(const std::vector<double> data);
};

#endif