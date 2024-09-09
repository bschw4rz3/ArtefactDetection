#ifndef MorletWaveletService_H
#define MorletWaveletService_H

#include <vector>
#include <complex>
#include <cmath>

#include "MathSerivce.h"
#include "WaveletResult.h"
#include "MultiplyResult.h"

class MorletWaveletService
{
private:
	MathSerivce* mathSerivce;

public:
	MorletWaveletService(MathSerivce* mathSerivce);
	
	WaveletResult calculate(std::vector<std::complex<double>> input);

private:
	std::complex<double> MorletWavelet(std::complex<double> t, double sigma, double omega0);
	std::complex<double> calculateWaveletFunction(std::complex<double> time, double w_0, double o);

	MultiplyResult convolve(const std::vector<std::complex<double>>& signal, const std::vector<std::complex<double>>& wavelet);
	MultiplyResult multiply(const std::vector<std::complex<double>>& signal, const std::vector<std::complex<double>>& wavelet);

};
#endif