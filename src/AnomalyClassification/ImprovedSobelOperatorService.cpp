#include "ImprovedSobelOperatorService.h"

ImprovedSobelOperatorService::ImprovedSobelOperatorService(ColorService* colorService)
{
	this->colorService = colorService;
}

CImg<unsigned char> ImprovedSobelOperatorService::getGradientImage(const CImg<unsigned char>& image)
{
	// Initialisiert ein 2-dimensionales Array für den Sobel-Operator S_x
	double S_x[3][3] = { {-1.0, 0.0, 1.0}, {-2.0, 0.0, 2.0}, {-1.0, 0.0, 1.0} };
	// Initialisiert ein 2-dimensionales Array für den Sobel-Operator S_y
	double S_y[3][3] = { {-1.0, -2.0, -1.0}, {0.0, 0.0, 0.0}, {1.0, 2.0, 1.0} };

	double S_45 [3][3] = { {-0.0, -1.0, -2.0}, {1.0, 0.0, 1.0}, {2.0, 1.0, 0.0} };
	double S_315[3][3] = { {-2.0, -1.0, -0.0}, {-1.0, 0.0, 1.0}, {0.0, 1.0, 2.0} };
	double S_270[3][3] = { {-1.0, -2.0, -1.0}, {0.0, 0.0, 0.0}, {1.0, 2.0, 1.0} };
	double S_225[3][3] = { {0.0, 1.0, 2.0}, {-1.0, 0.0, 1.0}, {-2.0, -1.0, 0.0} };
	double S_180[3][3] = { {1.0, 0.0, -1.0}, {2.0, 0.0, -2.0}, {1.0, 0.0, -1.0} };
	double S_135[3][3] = { {2.0, 1.0, 0.0}, {1.0, 0.0, -1.0}, {0.0, -1.0, -2.0} };

	std::map<KeyValuePair<int, int>, double*> operatorTemplates;
	operatorTemplates.insert(std::pair< KeyValuePair<int, int>, double*>(KeyValuePair<int, int>(0, 1), (double*) S_y));
	operatorTemplates.insert(std::pair< KeyValuePair<int, int>, double*>(KeyValuePair<int, int>(1, 1), (double*)S_45));
	operatorTemplates.insert(std::pair< KeyValuePair<int, int>, double*>(KeyValuePair<int, int>(1, 0), (double*)S_x));
	operatorTemplates.insert(std::pair< KeyValuePair<int, int>, double*>(KeyValuePair<int, int>(1, -1), (double*)S_315));
	operatorTemplates.insert(std::pair< KeyValuePair<int, int>, double*>(KeyValuePair<int, int>(0, -1), (double*)S_270));
	operatorTemplates.insert(std::pair< KeyValuePair<int, int>, double*>(KeyValuePair<int, int>(-1, 0), (double*)S_180));
	operatorTemplates.insert(std::pair< KeyValuePair<int, int>, double*>(KeyValuePair<int, int>(-1, 1), (double*)S_135));

	// Erzeugt ein neues Bitmap für das Gradienten-Bild.

	const unsigned int size_z = 1;
	const unsigned int size_c = 3;

	CImg<unsigned char> gradientImage(image.width(), image.height(), size_z, size_c, 255);

	// Durchläuft das Originalbild entlang der x-Achse.
	for (int x = 0; x < image.width() - 2; x++)
	{
		// Durchläuft das Originalbild entlang der y-Achse.
		for (int y = 0; y < image.height() - 2; y++)
		{
			// Berechnet den Gradienten G_x
			double G_x = (S_x[0][0] * this->getPixel(image, x, y).r) + (S_x[0][1] * this->getPixel(image, x + 1, y).r) + (S_x[0][2] * this->getPixel(image, x + 2, y).r) +
				(S_x[1][0] * this->getPixel(image, x, y + 1).r) + (S_x[1][1] * this->getPixel(image, x + 1, y + 1).r) + (S_x[1][2] * this->getPixel(image, x + 2, y + 1).r) +
				(S_x[2][0] * this->getPixel(image, x, y + 2).r) + (S_x[2][1] * this->getPixel(image, x + 1, y + 2).r) + (S_x[2][2] * this->getPixel(image, x + 2, y + 2).r);
			// Berechnet den Gradienten G_y
			double G_y = (S_y[0][0] * this->getPixel(image, x, y).r) + (S_y[0][1] * this->getPixel(image, x + 1, y).r) + (S_y[0][2] * this->getPixel(image, x + 2, y).r) +
				(S_y[1][0] * this->getPixel(image, x, y + 1).r) + (S_y[1][1] * this->getPixel(image, x + 1, y + 1).r) + (S_y[1][2] * this->getPixel(image, x + 2, y + 1).r) +
				(S_y[2][0] * this->getPixel(image, x, y + 2).r) + (S_y[2][1] * this->getPixel(image, x + 1, y + 2).r) + (S_y[2][2] * this->getPixel(image, x + 2, y + 2).r);

			// Berechnet den richtungsunabhängigen Gradienten G.
			int G = (int)sqrt((G_x * G_x) + (G_y * G_y));
			// Setzt den Farbwert für das Pixel des Gradienten-Bilds.
			this->setPixel(gradientImage, x, y, ColorRGB(G, G, G));
		}
	}
	return gradientImage; // Gibt das Gradienten-Bild als Rückgabewert der Methode zurück.
}

ColorRGB ImprovedSobelOperatorService::getPixel(const CImg<unsigned char>& image, int x, int y)
{
	const unsigned char* bytePixel = image.data(x, y);
	return this->colorService->byte2rgb(bytePixel, image.width(), image.height());
}

void ImprovedSobelOperatorService::setPixel(CImg<unsigned char>& image, int x, int y, ColorRGB colorRGB)
{
	const unsigned char* color = this->colorService->rgb2byte(colorRGB);
	image.draw_point(x, y, color);
}