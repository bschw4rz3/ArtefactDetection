#include "DaubechiesFourWaveletService.h"

DaubechiesFourWaveletService::DaubechiesFourWaveletService(ClassicSobelOperatorService* sobelService, CImgService* cImgService)
{
    this->sobelService = sobelService;
    this->cImgService = cImgService;
}

void DaubechiesFourWaveletService::calculate(const CImg<unsigned char>* image, ColorRGB backgroundColor, bool normalizedToCentriod, bool trueToConture)
{    
    CImg<unsigned char> contureImage = this->sobelService->getGradientImage(image);
    std::vector<std::complex<double>> inputVector = this->cImgService->getContureAsComplexVector(&contureImage, backgroundColor, normalizedToCentriod, trueToConture);
    /*
    for ()
    {

    }

    int n = inputVector.size();
    double* v = wavelet::daub4_transform(n, u);
    double* w = wavelet::daub4_transform_inverse(n, v);

    std::vector<double> daubTransform;
    std::vector<double> daubTransformInverse;
    
    for (int i = 0; i < n; i++)
    {
        uniform.push_back(u[i]);
        daubTransform.push_back(v[i]);
        daubTransformInverse.push_back(w[i]);
    }*/

    return;
}