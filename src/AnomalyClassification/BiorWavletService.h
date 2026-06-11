#ifndef BiorWavletService_H
#define BiorWavletService_H

#include <iostream>
#include <vector>
#include <complex>
#include <cmath>
#include <algorithm>
#include <map>

class BiorWavletService
{
public:
	BiorWavletService();

	std::map<double, std::vector<std::complex<double>>> calculate(std::vector<std::complex<double>> input, int scaleSteps = 5);

private:
	std::vector<double> generateWavelet(const std::vector<double>& wavelet, double scale, double translation, int signalSize);

	std::map<double, std::vector<std::complex<double>>> biorWaveletTransform(const std::vector<std::complex<double>>& input, const std::vector<double>& wavelet, int scaleSteps, int translationSteps);
	std::vector<double> biorWaveletCoefficients();
};

#endif