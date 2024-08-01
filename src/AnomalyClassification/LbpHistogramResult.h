#ifndef LbpHistogramResult_H
#define LbpHistogramResult_H

#include <map>

class LbpHistogramResult
{
private:
	std::map<int, int> lbpHistogram;
	std::map<std::string, int> uniformityHistogram;

public:
	LbpHistogramResult(std::map<int, int> lbpHistogram, std::map<std::string, int> uniformityHistogram)
	{
		this->lbpHistogram = lbpHistogram;
		this->uniformityHistogram = uniformityHistogram;
	}

	std::map<int, int> getLbpHistogram()
	{
		return this->lbpHistogram;
	}

	std::map<std::string, int> getUniformityHistogram()
	{
		return this->uniformityHistogram;
	}
};

#endif