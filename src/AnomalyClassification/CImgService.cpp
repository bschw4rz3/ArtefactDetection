#include "CImgService.h"

CImgService::CImgService(GeometricService* geometricService, ColorService* colorService)
{
    this->colorService = colorService;
    this->geometricService = geometricService;
}

ColorRGB CImgService::getPixel(const CImg<unsigned char>* image, int x, int y)
{
	const unsigned char* bytePixel = image->data(x, y);
	return this->colorService->byte2rgb(bytePixel, image->width(), image->height());
}

void CImgService::setPixel(CImg<unsigned char>* image, int x, int y, ColorRGB colorRGB)
{
	const unsigned char* color = this->colorService->rgb2byte(colorRGB);
	image->draw_point(x, y, color);
}

CImg<unsigned char> CImgService::transpose(CImg<unsigned char>* image)
{
    CImg<unsigned char> transposeMatrix(image->width(), image->height(), 32, 0);

    for(int x = 0 ; x < image->width() ; x++)
    {
        for(int y = 0 ; y < image->height() ; y++)
        {
            ColorRGB color = this->getPixel(image, x, y);
            this->setPixel(&transposeMatrix, x, y, color);
        }
    }

    return transposeMatrix;
}

double CImgService::sum(CImg<unsigned char>* image)
{
    double result = 0;

    for(int x = 0 ; x < image->width() ; x++)
    {
        for(int y = 0 ; y < image->height() ; y++)
        {
            ColorRGB color = this->getPixel(image, x, y);

            double value = (((double)color.r) + ((double)color.g) + ((double)color.b)) / 3;
            result += value;
        }
    }

    return result;
}


void CImgService::divide(CImg<unsigned char>* image, double value)
{
    for(int x = 0 ; x < image->width() ; x++)
    {
        for(int y = 0 ; y < image->height() ; y++)
        {
            ColorRGB color = this->getPixel(image, x, y);

            double grayValue = (((double)color.r) + ((double)color.g) + ((double)color.b)) / 3;

            if(grayValue != 0)
            {
                grayValue /= value;
                grayValue *= 255;

                this->setPixel(image, x, y, ColorRGB(grayValue, grayValue, grayValue));
            }
        }
    }
}

void CImgService::normalizeGrayMatrix(CImg<unsigned char>* image, int whitePixels, int blackPixels, double factor)
{
    double imageValueSum = this->sum(image);

    if(whitePixels > 255)
    {
        imageValueSum += whitePixels - 255;
    }
    else
    {
        ColorRGB color = this->getPixel(image, 255, 255);
        whitePixels = color.r;
    }

    if(blackPixels > 255)
    {
        imageValueSum += blackPixels - 255;
    }
    else
    {
        ColorRGB color = this->getPixel(image, 0, 0);
        blackPixels = color.r;
    }

    for(int x = 0 ; x < image->width() ; x++)
    {
        for(int y = 0 ; y < image->height() ; y++)
        {
            ColorRGB color = this->getPixel(image, x, y);

            double grayValue = (((double)color.r) + ((double)color.g) + ((double)color.b)) / 3;

            if(x == 0 && y == 0)
            {
                grayValue = blackPixels;
            }
            else if(x == 255 && y == 255)
            {
                grayValue = whitePixels;
            }

            if(grayValue != 0)
            {
                grayValue /= imageValueSum;
                grayValue *= 255;
                grayValue *= factor;

                this->setPixel(image, x, y, ColorRGB(grayValue, grayValue, grayValue));
            }
        }
    }
}

std::vector<std::complex<double>> CImgService::getContureAsComplexVector(CImg<unsigned char>* contureImage, ColorRGB backgroundColor, bool normalizedToCentriod)
{
    Point2D centriod(0, 0);
    std::vector<std::complex<double>> vector;

    int backgroundGrayColor = backgroundColor.getGrayValue();

    if (normalizedToCentriod)
    {
        centriod = this->geometricService->calculateCentroid(contureImage, backgroundColor);
    }

    for (int x = 0; x < contureImage->width(); x++)
    {
        for (int y = 0; y < contureImage->height(); y++)
        {
            unsigned char* byteColor = contureImage->data(x, y);
            ColorRGB rgbColor = this->colorService->byte2rgb(byteColor, contureImage->width(), contureImage->height());
            int grayColor = rgbColor.getGrayValue();

            if (grayColor != backgroundGrayColor)
            {
                vector.push_back(std::complex<double>(x - centriod.x, y - centriod.y));
            }
        }
    }

    return vector;
}

