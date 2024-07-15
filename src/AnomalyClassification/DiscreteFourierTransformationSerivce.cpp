#include "DiscreteFourierTransformationSerivce.h"

DiscreteFourierTransformationSerivce::DiscreteFourierTransformationSerivce(ColorService* colorService)
{
	this->colorService = colorService;
}

std::vector<int> DiscreteFourierTransformationSerivce::calculate(CImg<unsigned char>* image)
{
	CImg<unsigned char> sobelImage = this->classicSobelOperatorService->getGradientImage(image);

	int len = 0;
	std::vector<float> xVector;
	std::vector<float> yVector;

	for (int x = 0; x < sobelImage.width(); x++)
	{
		for (int y = 0; y < sobelImage.height(); y++)
		{
			unsigned char* byteColor = sobelImage.data(x, y);
			ColorRGB rgbColor = this->colorService->byte2rgb(byteColor, sobelImage.width(), sobelImage.height());
			int grayColor = rgbColor.getGrayValue();

			if (grayColor == 255)
			{
				xVector.push_back(x);
				yVector.push_back(y);
				len++;
			}
		}
	}

	return this->calculate_IDFT(xVector, yVector, len);

}

std::vector<int> DiscreteFourierTransformationSerivce::calculate_IDFT(std::vector<float> Xr, std::vector<float> Xi, int len)
{
	std::vector<int> x(len, 0);
    int k, n, N = 0;

    for (n = 0; n < N; n++) {
        x[n] = 0;
        for (k = 0; k < N; k++) {
            int theta = (2 * M_PI * k * n) / N;
            x[n] = x[n] + Xr[k] * cos(theta)
                + Xi[k] * sin(theta);
        }
        x[n] = x[n] / N;
    }

    return x;
}

/*
void dft(const std::vector<std::complex<double>>& input, std::vector<std::complex<double>>& output)
{
	auto M_I_2PI_DL = -(6.28318530718i / (double)input.size());

	for (size_t k = 0; k < output.size(); ++k) {
		output[k] = 0;
		for (size_t n = 0; n < input.size(); ++n)
			output[k] += input[n] * pow(2.718281828459045, M_I_2PI_DL * (double)k * (double)n);
	}
}*/
