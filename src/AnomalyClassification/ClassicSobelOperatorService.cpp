#include "ClassicSobelOperatorService.h"

int ClassicSobelOperatorService::cacheImageWidth = 0;
int ClassicSobelOperatorService::cacheImageHeight = 0;
CImg<unsigned char> ClassicSobelOperatorService::cacheSobelImage;

ClassicSobelOperatorService::ClassicSobelOperatorService(ColorService* colorService)
{
	this->colorService = colorService;
}

CImg<unsigned char> ClassicSobelOperatorService::getGradientImage(const CImg<unsigned char>* image)
{
	if(image->width() == ClassicSobelOperatorService::cacheImageWidth && image->height() == ClassicSobelOperatorService::cacheImageHeight)
	{
		return ClassicSobelOperatorService::cacheSobelImage;
	}

	// Initialisiert ein 2-dimensionales Array für den Sobel-Operator S_x
	double S_x[3][3] = { {-1.0, 0.0, 1.0}, {-2.0, 0.0, 2.0}, {-1.0, 0.0, 1.0} };

	// Initialisiert ein 2-dimensionales Array für den Sobel-Operator S_y
	double S_y[3][3] = { {-1.0, -2.0, -1.0}, {0.0, 0.0, 0.0}, {1.0, 2.0, 1.0} };

	// Erzeugt ein neues Bitmap für das Gradienten-Bild.

	const unsigned int size_z = 1;
	const unsigned int size_c = 3;

	CImg<unsigned char> gradientImage(image->width(), image->height(), size_z, size_c, 255);

	// Durchläuft das Originalbild entlang der x-Achse.
	for (int x = 1; x < image->width() - 1; x++)
	{
		// Durchläuft das Originalbild entlang der y-Achse.
		for (int y = 1; y < image->height() - 1; y++)
		{
			double G_x = (S_x[0][0] * this->getPixel(image, (x-1), (y-1)).r)
                    + (S_x[0][1] * this->getPixel(image,  x   , (y-1)).r)
                    + (S_x[0][2] * this->getPixel(image, (x+1), (y-1)).r)
                    + (S_x[1][0] * this->getPixel(image, (x-1),  y   ).r)
                    + (S_x[1][1] * this->getPixel(image,  x   ,  y   ).r)
                    + (S_x[1][2] * this->getPixel(image, (x+1),  y   ).r)
                    + (S_x[2][0] * this->getPixel(image, (x-1), (y+1)).r)
                    + (S_x[2][1] * this->getPixel(image,  x   , (y+1)).r)
                    + (S_x[2][2] * this->getPixel(image, (x+1), (y+1)).r);

            double G_y = (S_y[0][0] * this->getPixel(image, (x-1), (y-1)).r)
                    + (S_y[0][1] * this->getPixel(image,  x,    (y-1)).r)
                    + (S_y[0][2] * this->getPixel(image, (x+1), (y-1)).r)
                    + (S_y[1][0] * this->getPixel(image, (x-1),  y   ).r)
                    + (S_y[1][1] * this->getPixel(image,  x,     y   ).r)
                    + (S_y[1][2] * this->getPixel(image, (x+1),  y   ).r)
                    + (S_y[2][0] * this->getPixel(image, (x-1), (y+1)).r)
                    + (S_y[2][1] * this->getPixel(image,  x,    (y+1)).r)
                    + (S_y[2][2] * this->getPixel(image, (x+1), (y+1)).r);

			// Berechnet den richtungsunabhängigen Gradienten G.
			int G = (int)sqrt((G_x * G_x) + (G_y * G_y));

			if(G < 0) G = 0;
            if(G > 255) G = 255;

			// Setzt den Farbwert für das Pixel des Gradienten-Bilds.
			this->setPixel(&gradientImage, x, y, ColorRGB(G, G, G));
		}
	}

	ClassicSobelOperatorService::cacheImageWidth = image->width();
	ClassicSobelOperatorService::cacheImageHeight = image->height();
	ClassicSobelOperatorService::cacheSobelImage = gradientImage;

	return gradientImage; // Gibt das Gradienten-Bild als Rückgabewert der Methode zurück.
}

ColorRGB ClassicSobelOperatorService::getPixel(const CImg<unsigned char>* image, int x, int y)
{
	const unsigned char* bytePixel = image->data(x, y);
	return this->colorService->byte2rgb(bytePixel, image->width(), image->height());
}

void ClassicSobelOperatorService::setPixel(CImg<unsigned char>* image, int x, int y, ColorRGB colorRGB)
{
	const unsigned char* color = this->colorService->rgb2byte(colorRGB);
	image->draw_point(x, y, color);
}