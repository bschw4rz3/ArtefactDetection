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

	std::map<double, std::vector<double>> calculate();

private:
	std::map<double, std::vector<double>> computeScalogram(const std::vector<double>& signal, const std::vector<double>& frequencies, double dt);
	std::vector<std::complex<double>> convolution(const std::vector<double>& signal, const std::vector<std::complex<double>>& wavelet);
	std::vector<std::complex<double>> moreletWavelet(int n, double freq, double dt);

};

#endif