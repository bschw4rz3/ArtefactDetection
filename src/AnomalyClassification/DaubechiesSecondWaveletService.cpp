#include "DaubechiesSecondWaveletService.h"

DaubechiesSecondWaveletService::DaubechiesSecondWaveletService()
{
	// Daubechies 2 Coefficients
	const double sqrt3 = sqrt(3.0);
	const double denom = 4.0 * sqrt(2.0);

	this->low_pass_filter = {(1.0 + sqrt3) / denom, (3.0 + sqrt3) / denom,
	                         (3.0 - sqrt3) / denom, (1.0 - sqrt3) / denom};
	
	this->high_pass_filter = {(1.0 - sqrt3) / denom, -(3.0 - sqrt3) / denom,
                              (3.0 + sqrt3) / denom, -(1.0 + sqrt3) / denom};
}

// Convolution operation
std::vector<std::complex<double>> DaubechiesSecondWaveletService::convolve(const std::vector<std::complex<double>>& signal, const std::vector<std::complex<double>>& filter) 
{
    int n = signal.size();
    int m = filter.size();
    std::vector<std::complex<double>> result(n, std::complex<double>(0, 0));

    for (int i = 0; i < n-m; ++i) {
        for (int j = 0; j < m; ++j) {
            result[i + j] += signal[i] * filter[j];
        }
    }
    return result;
}

// Downsampling by 2
std::vector<std::complex<double>> DaubechiesSecondWaveletService::downsample(const std::vector<std::complex<double>>& signal) 
{
    std::vector<std::complex<double>> result;
    for (size_t i = 0; i < signal.size(); i += 2) {
        result.push_back(signal[i]);
    }
    return result;
}

// Daubechies Wavelet Transform (Single Level)
void DaubechiesSecondWaveletService::dbx_wavelet_transform(const std::vector<std::complex<double>>& input, std::vector<std::complex<double>>& approx, std::vector<std::complex<double>>& detail) 
{
    // Convolve input signal with low-pass and high-pass filters
    std::vector<std::complex<double>> low_pass_convolution = this->convolve(input, low_pass_filter);
    std::vector<std::complex<double>> high_pass_convolution = this->convolve(input, high_pass_filter);

    // Downsample the convolved signals
    approx = low_pass_convolution; //this->downsample(low_pass_convolution);
    detail = high_pass_convolution; //this->downsample(high_pass_convolution);
}

// Perform multiple levels of Wavelet Transform
std::map<int, std::vector<std::complex<double>>> DaubechiesSecondWaveletService::multi_level_wavelet(const std::vector<std::complex<double>>& input, int levels) 
{
    std::vector<std::complex<double>> current_signal = input;
    std::map<int, std::vector<std::complex<double>>> result;

    int i = 0;

    for (; i < levels; ++i) 
    {
        std::vector<std::complex<double>> approx, detail;
        this->dbx_wavelet_transform(current_signal, approx, detail);
        result.insert(std::pair<int, std::vector<std::complex<double>>>(i, detail)); // Save detail coefficients for each level
        current_signal = approx;  // Use approximation coefficients for the next level
    }

    result.insert(std::pair<int, std::vector<std::complex<double>>>(i, current_signal)); // Save the last approximation coefficients
    return result;
}

std::map<int, std::vector<std::complex<double>>> DaubechiesSecondWaveletService::calculate(std::vector<std::complex<double>>& input, int levels) 
{   
    // Berechne die Wavelet-Transformation
    return this->multi_level_wavelet(input, levels);
}
