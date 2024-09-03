#ifndef DFTResult_H
#define DFTResult_H

#include <opencv2/opencv.hpp>

class DFTResult
{
public:
	cv::Mat spectrumMagnitude;
	std::vector<double> radialProfile;
	std::vector<double> frequencies;

};

#endif DFTResult_H