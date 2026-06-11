#include "MorletWaveletServiceFFT.h"

MorletWaveletServiceFFT::MorletWaveletServiceFFT()
{

}

// Morelet-Wavelet-Funktion
std::vector<std::complex<double>> MorletWaveletServiceFFT::waveletFunction(int n, double freq, double dt)
    {
        std::vector<std::complex<double>> wavelet(n);
        double sigma = 1.0; // Breite des Gaußfilters
        for (int i = 0; i < n; ++i) {
            double t = (i - n / 2) * dt;
            double gauss = exp(-t * t / (2.0 * sigma * sigma));
            std::complex<double> complex_wave = std::complex<double>(cos(2 * M_PI * freq * t), sin(2 * M_PI * freq * t));
            wavelet[i] = gauss * complex_wave;
        }
        return wavelet;
}

// Konvolutionsfunktion
std::vector<std::complex<double>> MorletWaveletServiceFFT::convolution(const std::vector<std::complex<double>>& signal, const std::vector<std::complex<double>>& wavelet)
{
    int n = signal.size();
    std::vector<std::complex<double>> result(n);

    for (int i = 0; i < n; ++i) {
        std::complex<double> sum = 0;
        for (int j = 0; j < n; ++j) {
            if (i - j >= 0 && i - j < n) {
                sum += signal[j] * wavelet[i - j];
            }
        }
        result[i] = sum;
    }

    return result;
}

// Funktion zur Berechnung des Scalograms
std::map<double, std::vector<double>> MorletWaveletServiceFFT::computeScalogram(const std::vector<std::complex<double>>& signal, const std::vector<double>& frequencies, double dt)
{
    int n = signal.size();
    int m = frequencies.size();

    std::map<double, std::vector<double>> scalogram;

    for (int i = 0; i < m; ++i) {
        double freq = frequencies[i];
        std::vector<std::complex<double>> wavelet = this->waveletFunction(n, freq, dt);
        std::vector<std::complex<double>> conv_result = this->convolution(signal, wavelet);

        std::vector<double> conv_result_abs(conv_result.size(), 0);

        for (int j = 0; j < n; ++j) {
            conv_result_abs[j] = std::abs(conv_result[j]);
        }

        scalogram.insert(std::pair<double, std::vector<double>>(freq, conv_result_abs));
    }

    return scalogram;
}

std::map<double, std::vector<double>> MorletWaveletServiceFFT::calculate(std::vector<std::complex<double>> signal)
{
    // Beispielsignal: Sinus mit verrauschtem Signal
    int n = 1000;   
    double dt = 0.01;

    // Frequenzen für das Scalogram
    //std::vector<double> frequencies = { 1, 5, 10, 15, 20, 25, 30, 35, 40 };
    std::vector<double> frequencies;

    for (int i = 0;i <= 40; i++)
    {
        frequencies.push_back(i);
    }

    // Berechnung des Scalograms
    return this->computeScalogram(signal, frequencies, dt);
}