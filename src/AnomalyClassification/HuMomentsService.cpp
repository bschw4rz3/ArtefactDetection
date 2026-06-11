#include "HuMomentsService.h"

HuMomentsService::HuMomentsService(ColorService* colorService)
{
	this->colorService = colorService;
}

double HuMomentsService::calculateMoment(CImg<unsigned char>* image, double p, double q)
{
	double sum = 0;

	for(int x = 0 ; x < image->width() ; x++)
	{
		for(int y = 0 ; y < image->height() ; y++)
		{
			const unsigned char* bytePixel = image->data(x, y);
			ColorRGB color = this->colorService->byte2rgb(bytePixel, image->width(), image->height());

			sum += pow(x, p) * pow(y, q) * color.r;
		}
	}

	return sum;
}

double HuMomentsService::calculateMomentMu(CImg<unsigned char>* image, double p, double q)
{
	double sum = 0;

	double averageX = image->width()/2;
	double averageY = image->height()/2;

	for(int x = 0 ; x < image->width() ; x++)
	{
		for(int y = 0 ; y < image->height() ; y++)
		{
			const unsigned char* bytePixel = image->data(x, y);
			ColorRGB color = this->colorService->byte2rgb(bytePixel, image->width(), image->height());

			sum += pow(x-averageX, p) * pow(y-averageY, q) * color.r;
		}
	}

	return sum;
}

double HuMomentsService::calculateMomentEta(CImg<unsigned char>* image, double p, double q, bool useMu)
{
	double mu = 0;
	double muZero = 0;

	int y = ((p + q)/2) + 1; 

	if(useMu)
	{
		mu = this->calculateMomentMu(image, p, q);
		muZero = this->calculateMomentMu(image, 0, 0);
	}
	else
	{
		mu = this->calculateMoment(image, p, q);
		muZero = this->calculateMoment(image, 0, 0);
	}

	return mu / pow(muZero, y);
}

double HuMomentsService::calculateHu1(CImg<unsigned char>* image, bool useMu)
{
	double eta02 = this->calculateMomentEta(image, 0, 2, useMu);
	double eta20 = this->calculateMomentEta(image, 2, 0, useMu);

	return eta02 + eta20;
}

double HuMomentsService::calculateHu2(CImg<unsigned char>* image, bool useMu)
{
	double eta02 = this->calculateMomentEta(image, 0, 2, useMu);
	double eta20 = this->calculateMomentEta(image, 2, 0, useMu);
	double eta11 = this->calculateMomentEta(image, 1, 1, useMu);

	return pow(eta20 - eta02, 2) + pow(2*eta11, 2);
}

double HuMomentsService::calculateHu3(CImg<unsigned char>* image, bool useMu)
{
	double eta30 = this->calculateMomentEta(image, 3, 0, useMu);
	double eta12 = this->calculateMomentEta(image, 1, 2, useMu);
	double eta21 = this->calculateMomentEta(image, 2, 1, useMu);
	double eta03 = this->calculateMomentEta(image, 0, 3, useMu);

	return pow(eta30 - (3*eta12), 2) + pow((3*eta21) - eta03, 2);
}

double HuMomentsService::calculateHu4(CImg<unsigned char>* image, bool useMu)
{
	double eta30 = this->calculateMomentEta(image, 3, 0, useMu);
	double eta12 = this->calculateMomentEta(image, 1, 2, useMu);
	double eta21 = this->calculateMomentEta(image, 2, 1, useMu);
	double eta03 = this->calculateMomentEta(image, 0, 3, useMu);

	return pow(eta30 + eta12, 2) + pow(eta21 + eta03, 2);
}

double HuMomentsService::calculateHu5(CImg<unsigned char>* image, bool useMu)
{
	double eta30 = this->calculateMomentEta(image, 3, 0, useMu);
	double eta12 = this->calculateMomentEta(image, 1, 2, useMu);
	double eta21 = this->calculateMomentEta(image, 2, 1, useMu);
	double eta03 = this->calculateMomentEta(image, 0, 3, useMu);

	return ((eta30 - (3*eta12)) * (eta30 + eta12) * abs(pow(eta30 + eta12, 2) - (3*pow(eta21 + eta03, 2)))) + 
		   (((3*eta21) - eta03) * (eta21 + eta03) * abs((3*pow(eta30 + eta12, 2)) - pow(eta21 + eta03, 2)));
}

double HuMomentsService::calculateHu6(CImg<unsigned char>* image, bool useMu)
{
	double eta20 = this->calculateMomentEta(image, 2, 0, useMu);
	double eta02 = this->calculateMomentEta(image, 0, 2, useMu);
	double eta30 = this->calculateMomentEta(image, 3, 0, useMu);
	double eta12 = this->calculateMomentEta(image, 1, 2, useMu);
	double eta21 = this->calculateMomentEta(image, 2, 1, useMu);
	double eta03 = this->calculateMomentEta(image, 0, 3, useMu);
	double eta11 = this->calculateMomentEta(image, 1, 1, useMu);

	return ((eta20 - eta02) * abs(pow(eta30 + eta12, 2) - pow(eta21 + eta03, 2))) + ((4 * eta11) * (eta30 + eta12) * (eta21 + eta03));
}

double HuMomentsService::calculateHu7(CImg<unsigned char>* image, bool useMu)
{
	double eta21 = this->calculateMomentEta(image, 2, 1, useMu);
	double eta03 = this->calculateMomentEta(image, 0, 3, useMu);
	double eta30 = this->calculateMomentEta(image, 3, 0, useMu);
	double eta12 = this->calculateMomentEta(image, 1, 2, useMu);

	return (((3 * eta21) - eta03) * (eta30 + eta12) * abs(pow(eta30 + eta12, 2)-(3*pow(eta21 + eta03, 2)))) -
		   ((eta30 - (3 * eta12)) * (eta21 + eta03) * abs((3 * pow(eta30 + eta12, 2)) - pow(eta21 + eta03, 2)));
}