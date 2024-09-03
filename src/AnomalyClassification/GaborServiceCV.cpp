#include "GaborServiceCV.h"

std::vector<double> GaborServiceCV::calculate(std::string imagePath)
{
	cv::Mat image = cv::imread(imagePath);
	cv::cvtColor(image, image, cv::COLOR_BGR2GRAY);

	cv::Mat source;
	image.convertTo(source, CV_32F);

	// Get Gabor features
	std::vector<cv::Mat> gaborFeatures = this->getFeature(source);

	// Final feature vector  of the obtained Gabbor features
	std::vector<double> feature;

	for (int x = 0; x < gaborFeatures.size(); x++)
	{
		cv::Mat gaborMat = gaborFeatures[x];
		for (int y = 0; y < gaborMat.rows; y++)
		{
			const double* My = gaborMat.ptr<double>(y);
			for (int z = 0; z < gaborMat.cols; z++)
			{
				feature.push_back(My[z]);
			} // end of z-loop
		} // end of y-loop
	} // end of x-loop

	return feature;
}

std::vector<cv::Mat> GaborServiceCV::getFeature(cv::Mat& inputImage)
{
	if (inputImage.channels() > 1)
	{
		cv::cvtColor(inputImage, inputImage, cv::COLOR_BGR2GRAY);
	}

	int k = 1;
	int scaleSize = 5;
	int orientSize = 8;

	int R = inputImage.rows;
	int C = inputImage.cols;

	cv::Mat tar;
	std::vector<cv::Mat> G_img;

	inputImage.copyTo(tar);

	for (int v = 0; v < scaleSize; v++)
	{
		for (int u = 1; u <= orientSize; u++)
		{
			// Get gabor feature by convolving with Gabor wavelet
			cv::Mat GW = this->run(R, C, Kmax, f, u, v, Delt);
			cv::Mat chann[2], filterMat, Regabout;

			cv::split(GW, chann);
			cv::copyMakeBorder(chann[0], filterMat, 0, 0, 0, 0, cv::BORDER_CONSTANT);
			cv::filter2D(tar, Regabout, -1, filterMat);
			G_img.push_back(Regabout);

		} // end of u-loop
	} // end of v-loop

	return G_img;

} // end of function definition

cv::Mat GaborServiceCV::run(int R, int C, double Kmax, double f, double u, double v, double Delt2)
{
	double eR = std::cos(u * M_PI / 8);
	double eI = std::sin(u * M_PI / 8);

	double kR = (Kmax / std::pow(f, v)) * eR;
	double kI = (Kmax / std::pow(f, v)) * eI;

	double kn2R = std::pow(std::abs(kR), 2);
	double kn2I = std::pow(std::abs(kI), 2);
	double kn2 = std::pow(kn2R, 2) + std::pow(kn2I, 2);

	cv::Mat result = cv::Mat::zeros(R, C, CV_32F);
	cv::Mat realMat = cv::Mat::zeros(R, C, CV_32F);
	cv::Mat imagMat = cv::Mat::zeros(R, C, CV_32F);

	for (double m = -R / 2; m < R / 2; m++)
	{
		for (double n = -C / 2; n < C / 2; n++)
		{
			double waveR = std::cos(kR * m + kI * n);
			double waveI = std::sin(kR * m + kI * n);

			double term = (kn2 / Delt2) * std::exp(-0.5 * kn2 * (std::pow(m, 2) + std::pow(n, 2)) / Delt2);
			double valR = term * (waveR - std::exp(-0.5 * Delt2));
			double valI = term * (waveI - std::exp(-0.5 * Delt2));

			realMat.at<float>(m + R / 2, n + C / 2) = valR;
			imagMat.at<float>(m + R / 2, n + C / 2) = valI;
		} // end of n-loop
	} // end of m-loop

	std::vector<cv::Mat> channels;
	channels.push_back(realMat);
	channels.push_back(imagMat);
	cv::merge(channels, result);

	return result;
} // end of function definition