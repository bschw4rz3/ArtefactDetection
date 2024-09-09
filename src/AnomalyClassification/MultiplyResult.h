#ifndef MultiplyResult_H
#define MultiplyResult_H

#include <vector>
#include <complex>

class MultiplyResult
{
public:
	std::complex<double> sum;
	std::vector<std::complex<double>> convolvedSignal;

	MultiplyResult(std::complex<double> sum, std::vector<std::complex<double>> convolvedSignal)
	{
		this->sum = sum;
		this->convolvedSignal = convolvedSignal;
	}
};

#endif