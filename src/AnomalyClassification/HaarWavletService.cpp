#include "HaarWavletService.h"

HaarWavletService::HaarWavletService()
{

}

std::vector<std::complex<double>> HaarWavletService::waveletFunction(int n, double freq, double dt)
{
    std::vector<std::complex<double>> wavelet(n);
    double sigma = 1.0; 
    for (int i = 0; i < n; ++i) {
        double t = (i - n / 2) * dt;
        double gauss = i < 5 ? 1 : -1;
        std::complex<double> complex_wave = std::complex<double>(cos(2 * M_PI * freq * t), sin(2 * M_PI * freq * t));
        wavelet[i] = gauss * complex_wave;
    }

    return wavelet;
}