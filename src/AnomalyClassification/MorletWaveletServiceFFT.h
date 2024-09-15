#ifndef MorletWaveletServiceFFT_H
#define MorletWaveletServiceFFT_H

#include <iostream>
#include <vector>
#include <complex>
#include <cmath>
#include <map>

#include "MathSerivce.h"
//#include <fftw3/fftw3.h> // Für die FFTW-Transformation

class MorletWaveletServiceFFT
{
public:
	MorletWaveletServiceFFT();

	virtual std::map<double, std::vector<double>> calculate(std::vector<std::complex<double>> signal);

protected:
	virtual std::map<double, std::vector<double>> computeScalogram(const std::vector<std::complex<double>>& signal, const std::vector<double>& frequencies, double dt);
	virtual std::vector<std::complex<double>> convolution(const std::vector<std::complex<double>>& signal, const std::vector<std::complex<double>>& wavelet);
	virtual std::vector<std::complex<double>> waveletFunction(int n, double freq, double dt);

};

#endif