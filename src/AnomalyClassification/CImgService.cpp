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

std::vector<std::complex<double>> CImgService::getContureAsComplexVector(CImg<unsigned char>* contureImage, ColorRGB backgroundColor, bool normalizedToCentriod, bool trueToConture)
{
    Point2D centriod(0, 0);
    std::vector<std::complex<double>> vector;

    int backgroundGrayColor = backgroundColor.getGrayValue();

    if (normalizedToCentriod)
    {
        centriod = this->geometricService->calculateCentroid(contureImage, backgroundColor);
    }

    if (trueToConture)
    {
        vector = this->getContureByContureAsComplexVector(contureImage, backgroundGrayColor, centriod);
    }
    else
    {
        vector = this->getContureByColumnAsComplexVector(contureImage, backgroundGrayColor, centriod);
    }

    return vector;
}

std::vector<std::complex<double>> CImgService::getContureByContureAsComplexVector(CImg<unsigned char>* contureImage, int backgroundGrayColor, Point2D centriod)
{
    std::vector<std::complex<double>> resultVector;
    std::vector<std::vector<Point2D>> contureVectors;

    for (int x = 0; x < contureImage->width(); x++)
    {
        for (int y = 0; y < contureImage->height(); y++)
        {
            unsigned char* byteColor = contureImage->data(x, y);
            ColorRGB rgbColor = this->colorService->byte2rgb(byteColor, contureImage->width(), contureImage->height());
            int grayColor = rgbColor.getGrayValue();

            if (grayColor != backgroundGrayColor && !this->isIn(contureVectors, Point2D(x,y)))
            {
                Point2D currentPoint(x, y);
                std::vector<Point2D> contureVector;
                contureVector.push_back(currentPoint);
                this->addPointNear(currentPoint, contureImage, contureVector, backgroundGrayColor);
                
                contureVectors.push_back(contureVector);
            }
        }
    }

    for (int contureIndex = 0; contureIndex < contureVectors.size(); contureIndex++)
    {
        for (int pointIndex = 0; pointIndex < contureVectors[contureIndex].size(); pointIndex++)
        {
            Point2D current = contureVectors[contureIndex][pointIndex];
            resultVector.push_back(std::complex<double>(current.x, current.y));
        }
    }

    return resultVector;
}

void CImgService::addPointNear(Point2D currentPoint, CImg<unsigned char>* contureImage, std::vector<Point2D>& contureVector, int backgroundGrayColor)
{
    for (int cx = currentPoint.x - 2; cx <= currentPoint.x + 2; cx++)
    {
        for (int cy = currentPoint.y - 2; cy < currentPoint.y + 2; cy++)
        {
            if (cx < 0 || cx >= contureImage->width())
            {
                continue;
            }
            else if (cy < 0 || cy >= contureImage->height())
            {
                continue;
            }

            unsigned char* byteColor = contureImage->data(cx, cy);
            ColorRGB rgbColor = this->colorService->byte2rgb(byteColor, contureImage->width(), contureImage->height());
            int grayColor = rgbColor.getGrayValue();

            Point2D childPoint(cx, cy);

            if (grayColor != backgroundGrayColor)
            {
                if (!this->isIn(contureVector, childPoint))
                {
                    contureVector.push_back(childPoint);
                    this->addPointNear(childPoint, contureImage, contureVector, backgroundGrayColor);
                }
            }
        }
    }
}

bool CImgService::isIn(const std::vector<std::vector<Point2D>>& contureVectors, Point2D point)
{
    for (int contureIndex = 0; contureIndex < contureVectors.size(); contureIndex++)
    {
        if (this->isIn(contureVectors[contureIndex], point))
        {
            return true;
        }
    }

    return false;
}

bool CImgService::isIn(const std::vector<Point2D>& contureVector, Point2D point)
{
    for (int pointIndex = 0; pointIndex < contureVector.size(); pointIndex++)
    {
        Point2D currentPoint = contureVector[pointIndex];

        if (currentPoint == point)
        {
            return true;
        }
    }

    return false;
}

std::vector<std::complex<double>> CImgService::getContureByColumnAsComplexVector(CImg<unsigned char>* contureImage, int backgroundGrayColor, Point2D centriod)
{
    std::vector<std::complex<double>> vector;

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