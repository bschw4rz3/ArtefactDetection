#ifndef HuMomentsService_H
#define HuMomentsService_H

#define cimg_use_png
#pragma warning(disable:4146)
#pragma warning(disable:4996)
#include "../Shared/cimg/CImg.h"
using namespace cimg_library;

#include "ColorService.h"
#include "../IrrlichtWrapper/Point2D.h"

class HuMomentsService
{
private:
	ColorService* colorService;

public:
	HuMomentsService(ColorService* colorService);

	double calculateMoment(CImg<unsigned char>* image, double p, double q);
	double calculateMomentMu(CImg<unsigned char>* image, double p, double q);
	double calculateMomentEta(CImg<unsigned char>* image, double p, double q, bool useMu = true);

	double calculateHu1(CImg<unsigned char>* image, bool useMu = true);
	double calculateHu2(CImg<unsigned char>* image, bool useMu = true);
	double calculateHu3(CImg<unsigned char>* image, bool useMu = true);
	double calculateHu4(CImg<unsigned char>* image, bool useMu = true);
	double calculateHu5(CImg<unsigned char>* image, bool useMu = true);
	double calculateHu6(CImg<unsigned char>* image, bool useMu = true);
	double calculateHu7(CImg<unsigned char>* image, bool useMu = true);
};

#endif