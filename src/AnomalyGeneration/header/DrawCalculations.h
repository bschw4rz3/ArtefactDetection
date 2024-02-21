#ifndef _DRAWCALCULATIONS_
#define _DRAWCALCULATIONS_

#pragma warning(disable:4146)

#include <cstdlib>
#include <math.h>
#include "corecrt_math_defines.h"

#include "cimg/CImg.h"
using namespace cimg_library;

class DrawCalculations
{
public:
	void drawCicel(CImg<unsigned int>* bg, int xPos, int yPos, int r, const unsigned char (&color)[3]);
	void drawCicelCloud(CImg<unsigned int>* bg, int xPos, int yPos, int r, int steuerung, double pixelCountPerBoarderPixel, double pixelDistribution, const unsigned char (&color)[3]);

private:
	void drawPointFromCloud(CImg<unsigned int>* bg, int x, int y, int xPos, int yPos, int steuerung, int pixelCount, double pixelDistribution, const unsigned char (&color)[3]);
	int random(int steuerung, double pixelDistribution);
};

#endif // _DRAWCALCULATIONS_

