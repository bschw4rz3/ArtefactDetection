#include "DaubechiesFourWaveletService.h"

DaubechiesFourWaveletService::DaubechiesFourWaveletService()
{
    // Daubechies 4 Coefficients (low-pass filter)
    const double sqrt10 = sqrt(10.0);
    const std::complex<double> sqrt5_2_sqrt10_pos = sqrt(std::complex<double>(5.0 + 2.0 * sqrt10));
    const std::complex<double> sqrt5_2_sqrt10_neg = sqrt(std::complex<double>(5.0 - 2.0 * sqrt10));
    const double denom = 16.0 * sqrt(2.0);

    this->low_pass_filter = {
        (1.0 + sqrt10 + sqrt5_2_sqrt10_pos) / denom,
        (5.0 + sqrt10 - sqrt5_2_sqrt10_pos) / denom,
        (5.0 - sqrt10 + sqrt5_2_sqrt10_neg) / denom,
        (1.0 - sqrt10 - sqrt5_2_sqrt10_neg) / denom
    };

    // High-pass filter is derived from the low-pass filter by alternating signs and reversing the order
    this->high_pass_filter = {
        low_pass_filter[3], -low_pass_filter[2],
        low_pass_filter[1], -low_pass_filter[0]
    };
}

// Daubechies Wavelet Transform (Single Level)
void DaubechiesFourWaveletService::dbx_wavelet_transform(const std::vector<std::complex<double>>& input, std::vector<std::complex<double>>& approx, std::vector<std::complex<double>>& detail) {
    // Convolve input signal with low-pass and high-pass filters
    std::vector<std::complex<double>> low_pass_convolution = this->convolve(input, low_pass_filter);
    std::vector<std::complex<double>> high_pass_convolution = this->convolve(input, high_pass_filter);

    // Downsample the convolved signals
    approx = low_pass_convolution; //this->downsample(low_pass_convolution);
    detail = high_pass_convolution; //this->downsample(high_pass_convolution);
}

std::map<int, std::vector<std::complex<double>>> DaubechiesFourWaveletService::calculate(std::vector<std::complex<double>> input, int levels)
{  
    // Berechne die Wavelet-Transformation
    return this->multi_level_wavelet(input, levels);


}