#ifndef GaborServiceCV_h
#define GaborServiceCV_h

#include <string>
#include <vector>

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/gapi/imgproc.hpp>
#include <opencv2/gapi/gkernel.hpp>
#include <opencv2/gapi/gmat.hpp>
#include <opencv2/gapi/gscalar.hpp>
#include <opencv2/imgproc.hpp>

#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/core/core.hpp"

#include "MathSerivce.h"

class GaborServiceCV
{
private:
	double Kmax = M_PI / 2;
	double f = std::sqrt(2);
	double Delt = 2 * M_PI;

public:
	std::vector<double> calculate(std::string imagePath);

private:
	cv::Mat run(int R, int C, double Kmax, double f, double u, double v, double Delt2);
	std::vector<cv::Mat> getFeature(cv::Mat& inputImage);
};

#endif