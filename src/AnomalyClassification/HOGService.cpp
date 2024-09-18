#include "HOGService.h"

HOGService::HOGService(ClassicSobelOperatorService* sobelService, CImgService* cImgService, MathSerivce* mathService)
{
	this->sobelService = sobelService;
	this->cImgService = cImgService;
	this->mathService = mathService;
}

std::vector<double> HOGService::calculate(const CImg<unsigned char>* image, int blockSize, int maxPixelLengthPerCell, int bins)
{
	std::vector<double> result;

	HogCellResult cellResult = this->calculateCells(image, maxPixelLengthPerCell, bins);

	if(!cellResult.success)
	{
		return result;
	}

	Point2D lastPoint = cellResult.lastPoint;
	std::map<Point2D, std::vector<double>> cellResults = cellResult.cellResults;

	double blockCountX = ((double)lastPoint.x) / ((double) blockSize); 
	double blockCountY = ((double)lastPoint.y) / ((double) blockSize); 

	for(int blockX = 0 ; blockX <= blockCountX ; blockX++)
	{
		for(int blockY = 0 ; blockY <= blockCountY ; blockY++)
		{
			std::vector<double> blockHistogram;

			for(int cellX = 0; cellX < blockSize ;cellX++)
			{
				for(int cellY = 0; cellY < blockSize ;cellY++)
				{
					Point2D currentCell((blockX*blockSize)+cellX, (blockY*blockSize)+cellY);
					std::vector<double> cellHistogram = cellResults[currentCell];

					for(int i = 0;i < cellHistogram.size();i++)
					{
						blockHistogram.push_back(cellHistogram[i]);
					}
				}
			}

			std::vector<double> normBlockHistogram = this->norm(blockHistogram);

			for(int i = 0;i < normBlockHistogram.size();i++)
			{
				result.push_back(normBlockHistogram[i]);
			}
		}
	}

	return result;
}

std::vector<double> HOGService::norm(const std::vector<double>& blockHistogram)
{
	std::vector<double> result;
	double normTeiler = 0;

	for(int i = 0;i < blockHistogram.size();i++)
	{
		normTeiler += pow(blockHistogram[i], 2);
	}

	normTeiler = sqrt(normTeiler);

	if(normTeiler > 0)
	{
		for(int i = 0;i < blockHistogram.size();i++)
		{
			result.push_back(blockHistogram[i]/normTeiler);
		}
	}
	else
	{
		result = blockHistogram;
	}

	return result;
}

HogCellResult HOGService::calculateCells(const CImg<unsigned char>* image, int maxPixelLengthPerBlock, int bins)
{
	const unsigned int size_z = 1;
    const unsigned int size_c = 3;

	std::vector<double> degreeBins = this->getDegreeBins(bins);

	int widthCellCount = ceil(image->width() / maxPixelLengthPerBlock);
	int heightCellCount = ceil(image->height() / maxPixelLengthPerBlock);

	double cellWidth = ((double)image->width()) / ((double)widthCellCount); 
	double cellHeight = ((double)image->height()) / ((double)heightCellCount);

	if(isnan(cellWidth) || isnan(cellHeight)  || isinf(cellWidth) || isinf(cellHeight))
	{
		//"HOG: Zellengröße nicht berrechenbar. Bild vermutlich zu klein";
		return HogCellResult();
	}

	Point2D lastPoint;
	std::map<Point2D, std::vector<double>> cellResults;

	int x = 0;
	for(double beginX = 0 ; beginX < image->width() ; beginX += cellWidth)
	{
		int y = 0;
		for(double beginY = 0 ; beginY < image->height() ; beginY += cellHeight)
		{
			CImg<unsigned char> partImage = image->get_crop(beginX, beginY, 0, 0, round(beginX + cellWidth), round(beginY + cellHeight), 0, size_c);
			std::vector<double> thetaHistogram = this->calculateGradientenMagnitude(&partImage, degreeBins);

			lastPoint = Point2D(x, y);
			cellResults.insert(std::pair<Point2D, std::vector<double>>(lastPoint, thetaHistogram));

			y++;
		}
		x++;
	}

	return HogCellResult(cellResults, lastPoint);
}

std::vector<double> HOGService::calculateGradientenMagnitude(const CImg<unsigned char>* partImage, const std::vector<double>& degreeBins)
{
	std::vector<double> thetaHistogram(degreeBins.size());

	for(double x = 1 ; x < partImage->width() -1 ; x++)
	{
		for(double y = 1 ; y < partImage->height() -1 ; y++)
		{
			double diffX = this->calculateGradientX(partImage, x, y);
			double diffY = this->calculateGradientY(partImage, x, y);

			double gradient = abs(sqrt(pow(diffX, 2) + pow(diffY, 2)));

			double theta = 0;

			if(diffX == 0 && diffY != 0)
			{
				if(diffY > 0)
				{
					theta = 90; 
				}
				else if(diffY < 0)
				{
					theta = -90;
				}
			}
			else
			{
				theta = this->mathService->atanDegrees(diffY/diffX);
			}

			if(isinf(theta) || isnan(theta))
			{
				theta = 0;
			}

			if(theta < 0)
			{
				theta = 360 + theta;

				if(theta > 180)
				{
					theta = theta - 180;
				}
			}

			int thetaIndex = this->getBin(theta, degreeBins);
			thetaHistogram[thetaIndex]+=gradient;
		}
	}

	return thetaHistogram;
}

double HOGService::calculateGradientX(const CImg<unsigned char>* partImage, int x, int y)
{
	ColorRGB colorPlusX = this->cImgService->getPixel(partImage, x + 1, y);
	ColorRGB colorMinusX = this->cImgService->getPixel(partImage, x - 1, y);

	return ((colorPlusX.r - colorMinusX.r) + (colorPlusX.g - colorMinusX.g) + (colorPlusX.b - colorMinusX.b))/3;
}

double HOGService::calculateGradientY(const CImg<unsigned char>* partImage, int x, int y)
{
	ColorRGB colorPlus = this->cImgService->getPixel(partImage, x, y+ 1);
	ColorRGB colorMinus = this->cImgService->getPixel(partImage, x, y- 1);

	return ((colorPlus.r - colorMinus.r) + (colorPlus.g - colorMinus.g) + (colorPlus.b - colorMinus.b))/3;
}

std::vector<double> HOGService::getDegreeBins(int binCount)
{
	std::vector<double> result;
	double binStep = 180.0 / binCount;

	for(int i = 0; i <= binCount;i++)
	{
		result.push_back(i*binStep);
	}

	return result;
}

int HOGService::getBin(double degree, const std::vector<double>& degreeBins)
{
	for(int i = 0; i < degreeBins.size() ;i++)
	{
		if(degree <= degreeBins[i])
		{
			return i;
		}
	}
}