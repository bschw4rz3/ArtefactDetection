#ifndef GLCMResult_H
#define GLCMResult_H

#define cimg_use_png
#pragma warning(disable:4146)
#pragma warning(disable:4996)
#include "../Shared/cimg/CImg.h"
using namespace cimg_library;

class GLCMResult
{
private:
	double energy;
	double contrast;
	double homogenity;
	double IDM;
	double entropy;
	double mean;

	CImg<unsigned char> glImage;

public:
	GLCMResult(double energy, double contrast, double homogenity, double IDM, double entropy, double mean, CImg<unsigned char> glImage)
	{
		this->energy = energy;
		this->contrast = contrast;
		this->homogenity = homogenity;
		this->IDM = IDM;
		this->entropy = entropy;
		this->mean = mean;
		this->glImage = glImage;
	}

	double getEnergy()
	{
		return this->energy;
	}

	double getContrast()
	{
		return this->contrast;
	}

	double getHomogenity()
	{
		return this->homogenity;
	}

	double getIDM()
	{
		return this->IDM;
	}

	double getEntropy()
	{
		return this->entropy;
	}

	double getMean()
	{
		return this->mean;
	}

	CImg<unsigned char> getGlImage()
	{
		return this->glImage;
	}
};

#endif