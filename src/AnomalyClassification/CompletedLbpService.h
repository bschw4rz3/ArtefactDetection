#ifndef CompletedLbpService_H
#define CompletedLbpService_H

#include "LbpService.h"

#define cimg_use_png
#pragma warning(disable:4146)
#pragma warning(disable:4996)
#include "../Shared/cimg/CImg.h"
using namespace cimg_library;

#include <string>

#include "ColorService.h"
#include "GeometricService.h"
#include "ColorRGB.h"
#include "MathSerivce.h"
#include "LbpResult.h"
#include "LbpHistogramResult.h"

class CompletedLbpService : public LbpService
{
public:
	CompletedLbpService(GeometricService* geometricService, MathSerivce* mathSerivce, ColorService* colorSerivce);

protected:
	virtual int functionS(double value);
	virtual double sign(double x);
};

#endif