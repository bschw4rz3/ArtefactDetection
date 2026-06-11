#ifndef WaveletResult_H
#define WaveletResult_H

#include <vector>
#include <complex>

#include "TimeFrequenceResult.h"

class WaveletResult
{
public:
	std::vector<std::complex<double>> waveletOutput;
	std::vector<std::complex<double>> convolvedSignal;
	std::vector<std::complex<double>> bScoreVector;
	TimeFrequenceResult frequenceTime;

	double bestHerz;
	double bestA;
	double bestB;

	WaveletResult(std::vector<std::complex<double>> waveletOutput, std::vector<std::complex<double>> convolvedSignal, double bestHerz, double bestA, double bestB, std::vector<std::complex<double>> bScoreVector, std::map<double, std::vector<double>> frequenceTime, double maxFrequence)
	{
		this->waveletOutput = waveletOutput;
		this->convolvedSignal = convolvedSignal;
		this->bScoreVector = bScoreVector;
		this->frequenceTime = TimeFrequenceResult(frequenceTime, maxFrequence);

		this->bestHerz = bestHerz;
		this->bestA = bestA;
		this->bestB = bestB;
	}
};

#endif