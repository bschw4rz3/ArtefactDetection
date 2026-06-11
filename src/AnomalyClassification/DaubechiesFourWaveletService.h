#ifndef DaubechiesFourWaveletService_H
#define DaubechiesFourWaveletService_H

#define cimg_use_png
#pragma warning(disable:4146)
#pragma warning(disable:4996)
#include "../Shared/cimg/CImg.h"
using namespace cimg_library;

#include <iostream>
#include <vector>
#include <complex>
#include <cmath>
#include <valarray>
#include <iostream>
#include <iomanip>
#include <vector>

#include "CImgService.h"
#include "ClassicSobelOperatorService.h"

#include "../WaveletLib/wavelet.h"
#include "DaubechiesSecondWaveletService.h"

class DaubechiesFourWaveletService : DaubechiesSecondWaveletService
{
public:
	DaubechiesFourWaveletService();

	std::map<int, std::vector<std::complex<double>>> calculate(std::vector<std::complex<double>> input, int levels = 3);

private:
    void dbx_wavelet_transform(const std::vector<std::complex<double>>& input, std::vector<std::complex<double>>& approx, std::vector<std::complex<double>>& detail);
};

#endif