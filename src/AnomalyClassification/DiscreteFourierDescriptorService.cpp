#include "DiscreteFourierDescriptorService.h"

DiscreteFourierDescriptorService::DiscreteFourierDescriptorService(ClassicSobelOperatorService* classicSobelOperatorService, CImgService* cImgService)
{
    this->classicSobelOperatorService = classicSobelOperatorService;
    this->cImgService = cImgService;
}

FDResult DiscreteFourierDescriptorService::calculate(CImg<unsigned char>* image)
{
    CImg<unsigned char> sobelImage = this->classicSobelOperatorService->getGradientImage(image);
    std::vector<std::complex<double>> contour = this->cImgService->getContureAsComplexVector(&sobelImage, ColorRGB(0, 0, 0));

    if(contour.size() <= 0)
    {
        return FDResult();
    }

    std::vector<std::complex<double>> frequence = this->computeFourierDescriptors(contour);

    if(frequence.size() <= 0)
    {
        return FDResult();
    }

    return FDResult(sobelImage, contour, frequence);
}

std::vector<std::complex<double>> DiscreteFourierDescriptorService::computeFourierDescriptors(const std::vector<std::complex<double>>& contour) 
{
    int N = contour.size();
    std::vector<std::complex<double>> descriptors(N);

    for (int k = 0; k < N; ++k) {
        std::complex<double> sum(0.0, 0.0);
        for (int n = 0; n < N; ++n) {
            double theta = -2.0 * M_PI * k * n / N;
            sum += contour[n] * std::complex<double>(cos(theta), sin(theta));
        }
        descriptors[k] = sum / static_cast<double>(N);
    }

    return descriptors;
}
