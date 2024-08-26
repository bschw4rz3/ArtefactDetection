#ifndef GLCMService_H
#define GLCMService_H

#define cimg_use_png
#pragma warning(disable:4146)
#pragma warning(disable:4996)
#include "../Shared/cimg/CImg.h"
using namespace cimg_library;

#include "CImgService.h"

#include "GLCMResult.h"
#include "ColorRGB.h"
#include <vector>

class GLCMService
{
private:
	CImgService* imgService;

public:
	GLCMService(CImgService* imgService);

	GLCMResult calculate(CImg<unsigned char>* image);
};

#endif