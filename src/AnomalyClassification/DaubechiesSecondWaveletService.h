#ifndef DaubechiesSecondWaveletService_H
#define DaubechiesSecondWaveletService_H

#include <iostream>
#include <vector>
#include <complex>
#include <cmath>
#include <valarray>
#include <map>

class DaubechiesSecondWaveletService
{
protected:
	// Daubechies 2 Coefficients
	std::vector<std::complex<double>> low_pass_filter;
	std::vector<std::complex<double>> high_pass_filter;
	
public:
	DaubechiesSecondWaveletService();

	std::map<int, std::vector<std::complex<double>>> calculate(std::vector<std::complex<double>>& signal, int levels = 3);

protected:
	virtual void dbx_wavelet_transform(const std::vector<std::complex<double>>& input, std::vector<std::complex<double>>& approx, std::vector<std::complex<double>>& detail);
	virtual std::map<int, std::vector<std::complex<double>>> multi_level_wavelet(const std::vector<std::complex<double>>& input, int levels);

	virtual std::vector<std::complex<double>> convolve(const std::vector<std::complex<double>>& signal, const std::vector<std::complex<double>>& filter);
	virtual std::vector<std::complex<double>> downsample(const std::vector<std::complex<double>>& signal);
};

#endif