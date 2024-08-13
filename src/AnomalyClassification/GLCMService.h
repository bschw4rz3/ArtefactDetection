#ifndef GLCMService_H
#define GLCMService_H

#define cimg_use_png
#pragma warning(disable:4146)
#pragma warning(disable:4996)
#include "../Shared/cimg/CImg.h"
using namespace cimg_library;

#include <vector>

class GLCMService
{
public:
	void calculate(CImg<unsigned char>* image, std::vector<double>* vec_energy);
};

#endif