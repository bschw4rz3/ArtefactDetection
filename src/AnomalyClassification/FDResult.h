#ifndef DFResult_H
#define DFResult_H

#include <vector>
#include <complex>
#include "CImgService.h"

class FDResult
{
public:
	std::vector<std::complex<double>> fequence;
	CImg<unsigned char> sobelImage;

	FDResult(CImg<unsigned char> sobelImage, std::vector<std::complex<double>> fequence)
	{
		this->fequence = fequence;
		this->sobelImage = sobelImage;
	}
};

#endif