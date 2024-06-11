#include "GeometricService.h"

GeometricService::GeometricService(ColorService* colorService)
{
	this->colorService = colorService;
}

int GeometricService::countBlackPixels(CImg<unsigned char> image)
{
	double pixelArea = 0;

	for (int x = 0; x < image.width() - 1; x++)
	{
		// Durchläuft das Originalbild entlang der y-Achse.
		for (int y = 0; y < image.height() - 1; y++)
		{
			const unsigned char* bytePixel = image.data(x, y);
			ColorRGB color = this->colorService->byte2rgb(bytePixel, image.width(), image.height());

			if (color.r < 155)
			{
				pixelArea++;
			}
		}
	}

	return pixelArea;
}