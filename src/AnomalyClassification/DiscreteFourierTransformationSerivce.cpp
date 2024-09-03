#include "DiscreteFourierTransformationSerivce.h"

DiscreteFourierTransformationSerivce::DiscreteFourierTransformationSerivce(ClassicSobelOperatorService* classicSobelOperatorService, ColorService* colorService)
{
	this->classicSobelOperatorService = classicSobelOperatorService;
	this->colorService = colorService;
}

/**
 * \brief Computes 1-dimensional DFT (discrete fourier transform) on given input.
 *
 * \param input  an array of complex numbers, possibly a signal in time-domain.
 * \param output a modifiable array to store the output in, if larger than input
 *               only elements past input length are changed and if smaller the
 *               result is truncated to output length.
 */
void dft(const std::vector<std::complex<double>>& input, std::vector<std::complex<double>>& output)
{
	auto M_I_2PI_DL = -(6.28318530718i / (double)input.size());

	for (size_t k = 0; k < output.size(); ++k) {
		output[k] = 0;
		for (size_t n = 0; n < input.size(); ++n)
			output[k] += input[n] * pow(2.718281828459045, M_I_2PI_DL * (double)k * (double)n);
	}
}

/**
 * \brief Computes 1-dimensional IDFT (inverse discrete fourier transform) on given input.
 *
 * \param input an array of complex numbers, possibly a DFT'd signal in frequency domain.
 * \param output a modifiable array to store the output in, if larger than input
 *               only elements past input length are changed and if smaller the
 *               result is truncated to output length.
 */
void idft(const std::vector<std::complex<double>>& input, std::vector<std::complex<double>>& output)
{
	for (size_t k = 0; k < output.size(); ++k) 
	{
		output[k] = 0;
		for (size_t n = 0; n < input.size(); ++n)
		{ 
			const std::complex<double> e = (6.28318530718i * (double)k * (double)n) / (double)input.size();
			std::complex<double> f = pow(2.718281828459045, e);
			output[k] += input[n] * f;
		}

		output[k] /= input.size();
	}
}

std::vector<std::complex<double>> DiscreteFourierTransformationSerivce::calculate(CImg<unsigned char>* image, int dataSetLength)
{
	std::vector<std::complex<double>> vector;
	CImg<unsigned char> sobelImage = this->classicSobelOperatorService->getGradientImage(image);

	for (int x = 0; x < sobelImage.width(); x++)
	{
		for (int y = 0; y < sobelImage.height(); y++)
		{
			unsigned char* byteColor = sobelImage.data(x, y);
			ColorRGB rgbColor = this->colorService->byte2rgb(byteColor, sobelImage.width(), sobelImage.height());
			int grayColor = rgbColor.getGrayValue();

			if (grayColor == 255)
			{
				vector.push_back(std::complex<double>(x, y));
			}

		}
	}

	std::vector<std::complex<double>> output(dataSetLength);
	dft(vector, output);

	return output;
}

std::vector<std::complex<double>> DiscreteFourierTransformationSerivce::calculate_dft(const std::vector<std::complex<double>>& signal)
{
	const std::complex<double> PI(3.14159, 0);       // PI
	const std::complex<double> IMAG_UNIT(0, 1);

	long N = signal.size();									// Number of samples
	std::vector<std::complex<double> > dft(N);   // DFT vector
	               
	std::complex<double> temp(0, 0);                // Temporary loop variable

	for (int k = 0; k < N; k++)
	{
		for (int n = 0; n < N; n++)
		{
			temp = std::complex<double>(double(-1 * 2 * k * n) / N, 0);
			dft[k] += signal[n] * exp(IMAG_UNIT * PI * temp) / ((double) N);
		}
	}

	return dft;
}