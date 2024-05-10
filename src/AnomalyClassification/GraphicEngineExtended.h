#ifndef GraphicEngineExtended_H
#define GraphicEngineExtended_H

#define cimg_use_png
#pragma warning(disable:4146)
#pragma warning(disable:4996)
#include "../../../Shared/cimg/CImg.h"
using namespace cimg_library;

#include "../IrrlichtWrapper/GraphicEngine.h"

#include "StringSerivce.h"

class GraphicEngineExtended : public GraphicEngine
{
private:
	StringSerivce* stringSerivce;

public:
	GraphicEngineExtended(StringSerivce* stringSerivce);

	//void addScaledImage(int id, Point2D position, const wchar_t* file);
};

#endif