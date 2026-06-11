#ifndef DiscreteFourierTransformationSerivceCV_H
#define DiscreteFourierTransformationSerivceCV_H

#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>

#include "DFTResult.h"

using namespace cv;

class DiscreteFourierTransformationSerivceCV
{

public:
	DFTResult calculate(std::string filename);

private:
	std::vector<double> calculateRadialProfile(const cv::Mat& magnitudeImage);
	std::vector<double> calculateFrequencies(int maxRadius, int width, int height, double samplingRate);
};

#endif