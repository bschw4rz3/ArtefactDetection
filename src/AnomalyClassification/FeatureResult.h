#ifndef FeatureResult_H
#define FeatureResult_H

#include <vector>

class FeatureResult
{
private:
	std::vector<double> featureVector;

public:
	FeatureResult(std::vector<double> featureVector)
	{
		this->featureVector = featureVector;
	}

	FeatureResult(double v1, double v2 = NAN, double v3 = NAN, double v4 = NAN, double v5 = NAN, double v6 = NAN, double v7 = NAN, double v8 = NAN, double v9 = NAN)
	{
		this->featureVector.push_back(v1);

		if(!isnan(v2))
			this->featureVector.push_back(v2);

		if(!isnan(v3))
			this->featureVector.push_back(v3);

		if(!isnan(v4))
			this->featureVector.push_back(v4);

		if(!isnan(v4))
			this->featureVector.push_back(v4);

		if(!isnan(v5))
			this->featureVector.push_back(v5);

		if(!isnan(v6))
			this->featureVector.push_back(v6);

		if(!isnan(v7))
			this->featureVector.push_back(v7);

		if(!isnan(v8))
			this->featureVector.push_back(v8);

		if(!isnan(v9))
			this->featureVector.push_back(v9);
	}
};

#endif