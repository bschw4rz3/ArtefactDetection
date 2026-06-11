#include "HistogramValueService.h"

HistogramValueService::HistogramValueService(ColorService* colorService)
{
	this->colorService = colorService;
}

double HistogramValueService::getMean(CImg<unsigned char>* image)
{
	double mean = 0;
	std::map<ColorRGB, double> histogram = this->getHistogram(image);

	for (std::map<ColorRGB, double>::iterator it = histogram.begin(); it != histogram.end(); ++it)
	{
		ColorRGB key = it->first;
		double grayValue = key.getGrayValue();
		double proability = it->second;

		mean += grayValue* proability;
	}

	return mean;
}

double HistogramValueService::getVariance(CImg<unsigned char>* image)
{
	double variance = 0;
	double mean = this->getMean(image);
	std::map<ColorRGB, double> histogram = this->getHistogram(image);

	for (std::map<ColorRGB, double>::iterator it = histogram.begin(); it != histogram.end(); ++it)
	{
		ColorRGB key = it->first;
		double grayValue = key.getGrayValue();
		double proability = it->second;

		variance += pow(grayValue - mean, 2) * proability;
	}

	variance = sqrt(variance);

	return variance;
}

double HistogramValueService::getSkewness(CImg<unsigned char>* image)
{
	double mean = this->getMean(image);
	double variance = this->getVariance(image);
	double result = 0;

	std::map<ColorRGB, double> histogram = this->getHistogram(image);

	for (std::map<ColorRGB, double>::iterator it = histogram.begin(); it != histogram.end(); ++it)
	{
		ColorRGB key = it->first;
		double grayValue = key.getGrayValue();
		double proability = it->second;

		result += pow(grayValue - mean, 3) * proability;
	}

	return (1.0 / pow(variance, 3)) * result;
}

double HistogramValueService::getKurtosis(CImg<unsigned char>* image)
{
	double mean = this->getMean(image);
	double variance = this->getVariance(image);
	double result = 0;

	std::map<ColorRGB, double> histogram = this->getHistogram(image);

	for (std::map<ColorRGB, double>::iterator it = histogram.begin(); it != histogram.end(); ++it)
	{
		ColorRGB key = it->first;
		double grayValue = key.getGrayValue();
		double proability = it->second;

		result += pow(grayValue - mean, 4) * proability;
	}

	return (1.0 / pow(variance, 4)) * result;
}

double HistogramValueService::getPower(CImg<unsigned char>* image)
{
	double result = 0;

	std::map<ColorRGB, double> histogram = this->getHistogram(image);

	for (std::map<ColorRGB, double>::iterator it = histogram.begin(); it != histogram.end(); ++it)
	{
		double proability = it->second;
		result += pow(proability, 2);
	}

	return result;
}

double HistogramValueService::getEntropy(CImg<unsigned char>* image)
{
	double result = 0;

	std::map<ColorRGB, double> histogram = this->getHistogram(image);

	for (std::map<ColorRGB, double>::iterator it = histogram.begin(); it != histogram.end(); ++it)
	{
		double proability = it->second;
		result += proability * log(proability);
	}

	return -result;
}

std::map<ColorRGB, double> HistogramValueService::getHistogram(CImg<unsigned char>* image)
{
	double totalPixels = 0;
	std::map<ColorRGB, double> result;
	
	const unsigned char* c = this->colorService->rgb2byte(ColorRGB(255, 0, 0));

	for (int x = 0; x < image->width(); x++)
	{
		for (int y = 0; y < image->height(); y++)
		{
			const unsigned char* bytePixel = image->data(x, y);
			ColorRGB color = this->colorService->byte2rgb(bytePixel, image->width(), image->height());

			if(result.find(color) == result.end())
			{
				result.insert(std::pair<ColorRGB, double>(color, 1));
			}
			else
			{
				result[color]++;
			}

			totalPixels++;
		}
	}

	for (std::map<ColorRGB, double>::iterator it = result.begin(); it != result.end(); ++it)
	{
		it->second = it->second / totalPixels;
	}

	return result;
}