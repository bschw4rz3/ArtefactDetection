#ifndef _DRAWCALCULATIONS_
#define _DRAWCALCULATIONS_

#pragma warning(disable:4146)

#include <iostream>
#include <format>
#include <cstdlib>
#include <math.h>
#include "corecrt_math_defines.h"

#include "cimg/CImg.h"
using namespace cimg_library;

#include "DrawCircelCalculations.h"
#include "RandomService.h"

class DrawCalculations
{
private:
	DrawCircelCalculations* drawCircelCalculations;

public:
	DrawCalculations(DrawCircelCalculations* drawCircelCalculations);

	void drawCicel(CImg<unsigned int>* bg, int xPos, int yPos, int r, const unsigned char (&color)[3]);
	void drawCicelCloud(CImg<unsigned int>* bg, int xPos, int yPos, int r, int steuerung, double pixelCountPerBoarderPixel, double pixelDistribution, double fadeFromTo, double fadeOutY, const unsigned char (&color)[3]);
};

#endif // _DRAWCALCULATIONS_

