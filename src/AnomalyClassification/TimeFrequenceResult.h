#ifndef TimeFrequenceResult_H
#define TimeFrequenceResult_H

#include <vector>
#include <complex>
#include <map>

class TimeFrequenceResult
{
public:
	double maxFrequence;
	std::map<double, std::vector<double>> frequenceTimeMap;

	TimeFrequenceResult() {}

	TimeFrequenceResult(std::map<double, std::vector<double>> frequenceTimeMap, double maxFrequence)
	{
		this->maxFrequence = maxFrequence;
		this->frequenceTimeMap = frequenceTimeMap;
	}

	double getMaxFrequence()
	{
		return this->maxFrequence;
	}

	std::vector<double> getTimeScala(double frequence)
	{
		return this->frequenceTimeMap[frequence];
	}
};

#endif
