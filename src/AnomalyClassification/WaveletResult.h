#ifndef WaveletResult_H
#define WaveletResult_H

#include <vector>
#include <complex>

class WaveletResult
{
public:
	std::vector<std::complex<double>> waveletOutput;
	std::vector<std::complex<double>> convolvedSignal;
	double bestB;
	std::vector<std::complex<double>> bScoreVector;
	std::vector<double> frequence;

	WaveletResult(std::vector<std::complex<double>> waveletOutput, std::vector<std::complex<double>> convolvedSignal, double bestB, std::vector<std::complex<double>> bScoreVector, std::vector<double> frequence)
	{
		this->waveletOutput = waveletOutput;
		this->convolvedSignal = convolvedSignal;
		this->bestB = bestB;
		this->bScoreVector = bScoreVector;
		this->frequence = frequence;
	}
};

#endif