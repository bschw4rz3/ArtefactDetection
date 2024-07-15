#include "DiscreteFourierTransformationSerivce.h"

DiscreteFourierTransformationSerivce::DiscreteFourierTransformationSerivce(ClassicSobelOperatorService* classicSobelOperatorService, GeometricService* geometricService, ColorService* colorService)
{
	this->classicSobelOperatorService = classicSobelOperatorService;
	this->geometricService = geometricService;
	this->colorService = colorService;
}

void DiscreteFourierTransformationSerivce::calculate(CImg<unsigned char>* image)
{
	Point2D defectFocus = this->geometricService->calculateDefectFocus(image);

	//CImg<unsigned char>* image = this->classicSobelOperatorService->getGradientImage(image);

}