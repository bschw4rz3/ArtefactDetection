#include "HistogramValueService.h"

int HistogramValueService::lastImageX = NAN;
int HistogramValueService::lastImageY = NAN;

double HistogramValueService::meanCache = NAN;
double HistogramValueService::varianceCache = NAN;
std::map<ColorRGB, double> HistogramValueService::histogramCache = std::map<ColorRGB, double>();

HistogramValueService::HistogramValueService(ColorService* colorService)
{
	this->colorService = colorService;
}

double HistogramValueService::getMean(CImg<unsigned char>* image)
{
	/*
	if (this->isLastImage(image) && !isnan(HistogramValueService::meanCache))
	{
		return HistogramValueService::meanCache;
	}
	else if(this->isLastImage(image))
	{*/
		HistogramValueService::resetCache();
	//}

	double mean = 0;
	std::map<ColorRGB, double> histogram = this->getHistogram(image);

	for (std::map<ColorRGB, double>::iterator it = histogram.begin(); it != histogram.end(); ++it)
	{
		ColorRGB key = it->first;
		double grayValue = key.getGrayValue();
		double proability = it->second;

		mean += grayValue* proability;
	}

	HistogramValueService::meanCache = mean;

	return mean;
}

double HistogramValueService::getVariance(CImg<unsigned char>* image)
{
	/*if (this->isLastImage(image) && !isnan(HistogramValueService::varianceCache))
	{
		return HistogramValueService::varianceCache;
	}
	else if (this->isLastImage(image))
	{*/
		HistogramValueService::resetCache();
	//}

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

	HistogramValueService::varianceCache = variance;
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
	/*if (this->isLastImage(image))
	{
		return HistogramValueService::histogramCache;
	}
	else
	{*/
		HistogramValueService::resetCache();
	//}

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

	HistogramValueService::lastImageX = image->width();
	HistogramValueService::lastImageY = image->height();
	HistogramValueService::histogramCache = result;

	return result;
}

/*
bool HistogramValueService::isLastImage(CImg<unsigned char>* image)
{
	return HistogramValueService::lastImageX == image->width() && HistogramValueService::lastImageY == image->height();
}*/

void HistogramValueService::resetCache()
{
	HistogramValueService::lastImageX = NAN;
	HistogramValueService::lastImageY = NAN;

	HistogramValueService::meanCache = NAN;
	HistogramValueService::varianceCache = NAN;
	HistogramValueService::histogramCache = std::map<ColorRGB, double>();
}