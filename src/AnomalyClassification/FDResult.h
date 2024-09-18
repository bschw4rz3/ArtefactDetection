#ifndef DFResult_H
#define DFResult_H

#include <vector>
#include <complex>
#include "CImgService.h"

class FDResult
{
public:
	std::vector<std::complex<double>> fequence;
	std::vector<std::complex<double>> contourVector;
	bool success;

	CImg<unsigned char> sobelImage;

	FDResult(CImg<unsigned char> sobelImage, std::vector<std::complex<double>> contourVector, std::vector<std::complex<double>> fequence)
	{
		this->fequence = fequence;
		this->contourVector = contourVector;
		this->sobelImage = sobelImage;

		this->success = true;
	}

	FDResult()
	{
		this->success = false;
	}

	bool getSuccess()
	{
		return this->success;
	}
};

#endif