#ifndef FeatureResult_H
#define FeatureResult_H

#include <vector>

class FeatureResult
{
private:
	bool success;
	std::vector<double> featureVector;

public:
	FeatureResult()
	{
		this->success = false;
	}

	FeatureResult(std::vector<double> featureVector)
	{
		this->success = true;
		this->featureVector = featureVector;
	}

	FeatureResult(double v1, double v2 = NAN, double v3 = NAN, double v4 = NAN, double v5 = NAN, double v6 = NAN, double v7 = NAN, double v8 = NAN, double v9 = NAN, double v10 = NAN, double v11 = NAN, double v12 = NAN, double v13 = NAN, double v14 = NAN)
	{
		this->success = false;

		if(!isnan(v1))
		{
			this->featureVector.push_back(v1);
			this->success = true;
		}
		
		if(!isnan(v2))
		{
			this->featureVector.push_back(v2);
			this->success = true;
		}
		
		if(!isnan(v3))
		{
			this->featureVector.push_back(v3);
			this->success = true;
		}
			
		if(!isnan(v4))
		{
			this->featureVector.push_back(v4);
			this->success = true;
		}
		
		if(!isnan(v5))
		{
			this->featureVector.push_back(v5);
			this->success = true;
		}
			
		if(!isnan(v6))
		{
			this->featureVector.push_back(v6);
			this->success = true;
		}
		
		if(!isnan(v7))
		{
			this->featureVector.push_back(v7);
			this->success = true;
		}
		
		if(!isnan(v8))
		{
			this->featureVector.push_back(v8);
			this->success = true;
		}
		
		if(!isnan(v9))
		{
			this->featureVector.push_back(v9);
			this->success = true;
		}

		if (!isnan(v10))
		{
			this->featureVector.push_back(v10);
			this->success = true;
		}

		if (!isnan(v11))
		{
			this->featureVector.push_back(v11);
			this->success = true;
		}

		if (!isnan(v12))
		{
			this->featureVector.push_back(v12);
			this->success = true;
		}

		if (!isnan(v13))
		{
			this->featureVector.push_back(v13);
			this->success = true;
		}

		if (!isnan(v14))
		{
			this->featureVector.push_back(v14);
			this->success = true;
		}
			
	}

	std::vector<double> getFeatureVector()
	{
		return this->featureVector;
	}

	bool getSuccess()
	{
		return this->success;
	}
};

#endif