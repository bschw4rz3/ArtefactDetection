#include "MorletWaveletService.h"

MorletWaveletService::MorletWaveletService(MathSerivce* mathSerivce)
{
	this->mathSerivce = mathSerivce;
}

WaveletResult MorletWaveletService::calculate(std::vector<std::complex<double>> signal)
{
    // Morlet-Wavelet definieren (als diskretes Wavelet)
    double omega0 = 5.0;  // Zentrale Frequenz
    double sigma = 1.0;   // Breite der Gauß-Hüllkurve

    double bestA = NAN;
    double bestB = NAN;
    //std::complex<double> maxMultiply = std::complex<double>(-(DBL_MAX), -(DBL_MAX));
    double frequencMax = -(DBL_MAX);
    std::vector<std::complex<double>> bestWaveletOutput;
    std::vector<std::complex<double>> bestConvolvedVector;
    std::vector<std::complex<double>> bMatches;
    std::vector<double> frequence;
    int waveletSize = signal.size();

    double a = 20;
    double b = -waveletSize / 2.0;

    //for (double a = -50; a <= 50; a++)
    {
        for (double b = -waveletSize / 2.0; b < waveletSize / 2.0; b += 0.5)
        {
            std::vector<std::complex<double>> waveletOutput;

            // Berechne das Morlet-Wavelet für verschiedene Zeitpunkte (diskret)
            for (int i = 0; i < waveletSize; i++)
            {
                double part = (i - waveletSize / 2.0);
                std::complex<double> output = this->calculateWaveletFunction((part / a) - b, omega0, sigma);
                waveletOutput.push_back(output);
            }

            MultiplyResult convolvedResult = this->multiply(signal, waveletOutput);

            // Faltung des Signals mit dem Morlet-Wavelet
            //MultiplyResult convolvedResult = this->convolve(signal, waveletOutput);

            double realA = convolvedResult.sum.real();
            //double realB = maxMultiply.real();

            double imagA = convolvedResult.sum.imag();
            //double imagB = maxMultiply.imag();
            
            double fequenceA = pow(realA, 2) + pow(imagA, 2);

            frequence.push_back(fequenceA);
            bMatches.push_back(std::complex<double>(realA, imagA));

            if (/*realA >= realB && imagA >= imagB*/ fequenceA > frequencMax)
            {
                bestA = a;
                bestB = b;
                bestWaveletOutput = waveletOutput;
                bestConvolvedVector = convolvedResult.convolvedSignal;
                frequencMax = fequenceA;
            }
        }
    }

    return WaveletResult(bestWaveletOutput, bestConvolvedVector, bestB, bMatches, frequence);
}

MultiplyResult MorletWaveletService::convolve(const std::vector<std::complex<double>>& signal, const std::vector<std::complex<double>>& wavelet)
{
    int signalSize = signal.size();
    int waveletSize = wavelet.size();

    std::vector<std::complex<double>> result(signalSize + waveletSize - 1, 0);
    std::complex<double> sum = 0;

    for (int n = 0; n < result.size(); ++n) 
    {
        for (int m = 0; m < waveletSize; ++m) 
        {
            if (n - m >= 0 && n - m < signalSize) 
            {
                result[n] += signal[n - m] * std::conj(wavelet[m]); // Multiplikation mit dem komplex-konjugierten Wavelet
                sum += signal[n - m] * std::conj(wavelet[m]);
            }
        }
    }

    return MultiplyResult(sum, result);
}

MultiplyResult MorletWaveletService::multiply(const std::vector<std::complex<double>>& signal, const std::vector<std::complex<double>>& wavelet)
{
    std::complex<double> result = 0;
    std::vector<std::complex<double>> complexList;

    for (int i = 0; i < signal.size(); ++i)
    {
        complexList.push_back(signal[i] * wavelet[i]);
        result += signal[i] * wavelet[i];
    }

    return MultiplyResult(result, complexList);
}

std::complex<double> MorletWaveletService::calculateWaveletFunction(std::complex<double> t, double omega0, double sigma)
{
    // Berechne die Gauß-Hüllkurve: e^(-t^2 / (2 * sigma^2))
    std::complex<double> gaussianEnvelope = exp(-std::norm(t) / (2 * sigma * sigma));

    // Berechne die komplexe Schwingung (e^(i * omega0 * t))
    std::complex<double> oscillation = exp(std::complex<double>(0, omega0) * t);

    // Kombiniere die Gauß-Hüllkurve mit der komplexen Schwingung
    return oscillation * gaussianEnvelope;
}