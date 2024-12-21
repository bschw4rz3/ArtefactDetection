#ifndef FeatureToClassifyResult_H
#define FeatureToClassifyResult_H

class FeatureToClassifyResult
{
public:
	std::vector<DataPoint> trainingData;
	std::vector<std::vector<double>> testData;

	std::string resultString;
	std::string errorMessage;

	FeatureToClassifyResult(std::vector<DataPoint> trainingData, std::vector<std::vector<double>> testData)
	{
		this->trainingData = trainingData;
		this->testData = testData;

		double avgSum = 0;

		for (int i = 0; i < this->testData.size(); i++)
		{
			double avg = 0;

			for (int j = 0; j < this->testData[i].size(); j++)
			{
				avg += this->testData[i][j];
			}

			avg /= (double)this->testData[i].size();
			avgSum += avg;
		}

		avgSum /= (double) this->testData.size();

		this->resultString = "" + (int) (avgSum);
	}

	FeatureToClassifyResult(std::string errorMessage)
	{
		this->errorMessage = errorMessage;
		this->resultString = "error";
	}
};

#endif