#ifndef _DRAWCALCULATIONS_
#define _DRAWCALCULATIONS_

#pragma warning(disable:4146)

#include "cimg/CImg.h"
using namespace cimg_library;

class DrawCalculations
{
public:
	void drawCicel(CImg<unsigned int>* bg, int xPos, int yPos, int r, const unsigned char (&color)[3]);
};

#endif // _DRAWCALCULATIONS_

