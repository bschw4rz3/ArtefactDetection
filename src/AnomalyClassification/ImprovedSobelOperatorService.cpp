#include "ImprovedSobelOperatorService.h"

ImprovedSobelOperatorService::ImprovedSobelOperatorService(ColorService* colorService)
{
	this->colorService = colorService;
}

CImg<unsigned char> ImprovedSobelOperatorService::getGradientImage(const CImg<unsigned char>* image)
{
	// Initialisiert ein 2-dimensionales Array für den Sobel-Operator S_x
	double S_x[3][3] = { {-1.0, 0.0, 1.0}, {-2.0, 0.0, 2.0}, {-1.0, 0.0, 1.0} };
	// Initialisiert ein 2-dimensionales Array für den Sobel-Operator S_y
	double S_y[3][3] = { {-1.0, -2.0, -1.0}, {0.0, 0.0, 0.0}, {1.0, 2.0, 1.0} };

	double S_45 [3][3] = { {-0.0, -1.0, -2.0}, {1.0, 0.0, -1.0}, {2.0, 1.0, 0.0} };
	double S_315[3][3] = { {-2.0, -1.0, -0.0}, {-1.0, 0.0, 1.0}, {0.0, 1.0, 2.0} };
	double S_270[3][3] = { {-1.0, -2.0, -1.0}, {0.0, 0.0, 0.0}, {1.0, 2.0, 1.0} };
	double S_225[3][3] = { {0.0, 1.0, 2.0}, {-1.0, 0.0, 1.0}, {-2.0, -1.0, 0.0} };
	double S_180[3][3] = { {1.0, 0.0, -1.0}, {2.0, 0.0, -2.0}, {1.0, 0.0, -1.0} };
	double S_135[3][3] = { {2.0, 1.0, 0.0}, {1.0, 0.0, -1.0}, {0.0, -1.0, -2.0} };
	/*
	std::map<KeyValuePair<int, int>, double*> operatorTemplates;
	operatorTemplates.insert(std::pair< KeyValuePair<int, int>, double*>(KeyValuePair<int, int>(0, 1), (double*) S_y));
	operatorTemplates.insert(std::pair< KeyValuePair<int, int>, double*>(KeyValuePair<int, int>(1, 1), (double*)S_45));
	operatorTemplates.insert(std::pair< KeyValuePair<int, int>, double*>(KeyValuePair<int, int>(1, 0), (double*)S_x));
	operatorTemplates.insert(std::pair< KeyValuePair<int, int>, double*>(KeyValuePair<int, int>(1, -1), (double*)S_315));
	operatorTemplates.insert(std::pair< KeyValuePair<int, int>, double*>(KeyValuePair<int, int>(0, -1), (double*)S_270));
	operatorTemplates.insert(std::pair< KeyValuePair<int, int>, double*>(KeyValuePair<int, int>(-1, 0), (double*)S_180));
	operatorTemplates.insert(std::pair< KeyValuePair<int, int>, double*>(KeyValuePair<int, int>(-1, 1), (double*)S_135));*/

	// Erzeugt ein neues Bitmap für das Gradienten-Bild.

	const unsigned int size_z = 1;
	const unsigned int size_c = 3;

	CImg<unsigned char> gradientImage(image->width(), image->height(), size_z, size_c, 0);

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

			double G_45 = (S_45[0][0] * this->getPixel(image, (x-1), (y-1)).r)
                    + (S_45[0][1] * this->getPixel(image,  x   , (y-1)).r)
                    + (S_45[0][2] * this->getPixel(image, (x+1), (y-1)).r)
                    + (S_45[1][0] * this->getPixel(image, (x-1),  y   ).r)
                    + (S_45[1][1] * this->getPixel(image,  x   ,  y   ).r)
                    + (S_45[1][2] * this->getPixel(image, (x+1),  y   ).r)
                    + (S_45[2][0] * this->getPixel(image, (x-1), (y+1)).r)
                    + (S_45[2][1] * this->getPixel(image,  x   , (y+1)).r)
                    + (S_45[2][2] * this->getPixel(image, (x+1), (y+1)).r);

			double G_315 = (S_315[0][0] * this->getPixel(image, (x-1), (y-1)).r)
                    + (S_315[0][1] * this->getPixel(image,  x   , (y-1)).r)
                    + (S_315[0][2] * this->getPixel(image, (x+1), (y-1)).r)
                    + (S_315[1][0] * this->getPixel(image, (x-1),  y   ).r)
                    + (S_315[1][1] * this->getPixel(image,  x   ,  y   ).r)
                    + (S_315[1][2] * this->getPixel(image, (x+1),  y   ).r)
                    + (S_315[2][0] * this->getPixel(image, (x-1), (y+1)).r)
                    + (S_315[2][1] * this->getPixel(image,  x   , (y+1)).r)
                    + (S_315[2][2] * this->getPixel(image, (x+1), (y+1)).r);

			double G_270 = (S_270[0][0] * this->getPixel(image, (x-1), (y-1)).r)
                    + (S_270[0][1] * this->getPixel(image,  x   , (y-1)).r)
                    + (S_270[0][2] * this->getPixel(image, (x+1), (y-1)).r)
                    + (S_270[1][0] * this->getPixel(image, (x-1),  y   ).r)
                    + (S_270[1][1] * this->getPixel(image,  x   ,  y   ).r)
                    + (S_270[1][2] * this->getPixel(image, (x+1),  y   ).r)
                    + (S_270[2][0] * this->getPixel(image, (x-1), (y+1)).r)
                    + (S_270[2][1] * this->getPixel(image,  x   , (y+1)).r)
                    + (S_270[2][2] * this->getPixel(image, (x+1), (y+1)).r);

			double G_225 = (S_225[0][0] * this->getPixel(image, (x-1), (y-1)).r)
                    + (S_225[0][1] * this->getPixel(image,  x   , (y-1)).r)
                    + (S_225[0][2] * this->getPixel(image, (x+1), (y-1)).r)
                    + (S_225[1][0] * this->getPixel(image, (x-1),  y   ).r)
                    + (S_225[1][1] * this->getPixel(image,  x   ,  y   ).r)
                    + (S_225[1][2] * this->getPixel(image, (x+1),  y   ).r)
                    + (S_225[2][0] * this->getPixel(image, (x-1), (y+1)).r)
                    + (S_225[2][1] * this->getPixel(image,  x   , (y+1)).r)
                    + (S_225[2][2] * this->getPixel(image, (x+1), (y+1)).r);

			double G_180 = (S_180[0][0] * this->getPixel(image, (x-1), (y-1)).r)
                    + (S_180[0][1] * this->getPixel(image,  x   , (y-1)).r)
                    + (S_180[0][2] * this->getPixel(image, (x+1), (y-1)).r)
                    + (S_180[1][0] * this->getPixel(image, (x-1),  y   ).r)
                    + (S_180[1][1] * this->getPixel(image,  x   ,  y   ).r)
                    + (S_180[1][2] * this->getPixel(image, (x+1),  y   ).r)
                    + (S_180[2][0] * this->getPixel(image, (x-1), (y+1)).r)
                    + (S_180[2][1] * this->getPixel(image,  x   , (y+1)).r)
                    + (S_180[2][2] * this->getPixel(image, (x+1), (y+1)).r);

			double G_135 = (S_135[0][0] * this->getPixel(image, (x-1), (y-1)).r)
                    + (S_135[0][1] * this->getPixel(image,  x   , (y-1)).r)
                    + (S_135[0][2] * this->getPixel(image, (x+1), (y-1)).r)
                    + (S_135[1][0] * this->getPixel(image, (x-1),  y   ).r)
                    + (S_135[1][1] * this->getPixel(image,  x   ,  y   ).r)
                    + (S_135[1][2] * this->getPixel(image, (x+1),  y   ).r)
                    + (S_135[2][0] * this->getPixel(image, (x-1), (y+1)).r)
                    + (S_135[2][1] * this->getPixel(image,  x   , (y+1)).r)
                    + (S_135[2][2] * this->getPixel(image, (x+1), (y+1)).r);

			// Berechnet den richtungsunabhängigen Gradienten G.
			int G = (int)sqrt(pow(G_x, 2) + pow(G_y, 2) + pow(G_45, 2) + pow(G_315, 2) + pow(G_270, 2) + pow(G_225, 2) + pow(G_180, 2) + pow(G_135, 2));
			
			if(G < 0) 
                G = 0;

            if(G > 255) 
                G = 255;

			// Setzt den Farbwert für das Pixel des Gradienten-Bilds.
			this->setPixel(&gradientImage, x, y, ColorRGB(G, G, G));
		}
	}
	return gradientImage; // Gibt das Gradienten-Bild als Rückgabewert der Methode zurück.
}

ColorRGB ImprovedSobelOperatorService::getPixel(const CImg<unsigned char>* image, int x, int y)
{
	const unsigned char* bytePixel = image->data(x, y);
	return this->colorService->byte2rgb(bytePixel, image->width(), image->height());
}

void ImprovedSobelOperatorService::setPixel(CImg<unsigned char>* image, int x, int y, ColorRGB colorRGB)
{
	const unsigned char* color = this->colorService->rgb2byte(colorRGB);
	image->draw_point(x, y, color);
}