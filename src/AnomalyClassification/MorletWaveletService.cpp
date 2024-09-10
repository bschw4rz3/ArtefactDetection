#include "MorletWaveletService.h"

MorletWaveletService::MorletWaveletService(MathSerivce* mathSerivce)
{
	this->mathSerivce = mathSerivce;
}

WaveletResult MorletWaveletService::calculate(std::vector<std::complex<double>> signal, double maxHerz, double timeFactor)
{
    // Morlet-Wavelet definieren (als diskretes Wavelet)
    double omega0 = 5.0;  // Zentrale Frequenz
    double sigma = 1.0;   // Breite der Gauß-Hüllkurve
    double fitTolerance = 0.00000000000000000000001;

    double bestA = NAN;
    double bestB = NAN;
    double bestHerz = NAN;

    //std::complex<double> maxMultiply = std::complex<double>(-(DBL_MAX), -(DBL_MAX));
    double frequencMax = -(DBL_MAX);
    std::vector<std::complex<double>> bestWaveletOutput;
    std::vector<std::complex<double>> bestConvolvedVector;
    std::vector<std::complex<double>> bMatches;
    std::vector<std::complex<double>> bestMatches;
    std::map<double, std::vector<double>> frequenceTime;

    int waveletSize = signal.size();

    double a = 20;
    double b = -waveletSize / 2.0;

    for (double herz = 0; herz <= maxHerz+1; herz++)
    {
        a = 1 / herz;

        std::vector<double> timeVector;
        bool currentBest = false;

        //double bOffset = this->calculateWaveletFunctionOffset(timeFactor, omega0, sigma, a, fitTolerance);
        double bOffset = 0;


        for (double b = 0; b < waveletSize; b += 1)
        {
            if (b < bOffset || waveletSize - bOffset < b)
            {
                timeVector.push_back(0);
                bMatches.push_back(std::complex<double>(0, 0));
            }
            else
            { 
                std::vector<std::complex<double>> waveletOutput;

                // Berechne das Morlet-Wavelet für verschiedene Zeitpunkte (diskret)
                for (int t = 0; t < waveletSize; t++)
                {
                    //double part = (t - waveletSize / 2.0);
                    double time = t * timeFactor;
                    double timeValue = (time / a) - (b * timeFactor);

                    std::complex<double> output = this->calculateWaveletFunction(timeValue, omega0, sigma);
                    waveletOutput.push_back(output);
                }

                MultiplyResult convolvedResult = this->multiply(signal, waveletOutput);
            
                if (isnan(convolvedResult.sum.real()) || isinf(a))
                {
                    timeVector.push_back(0);
                    bMatches.push_back(std::complex<double>(0, 0));
                }
                else
                {
                    double realA = convolvedResult.sum.real();
                    double imagA = convolvedResult.sum.imag();

                    double fequenceA = sqrt(pow(realA, 2) + pow(imagA, 2));
                    //double fequenceA = this->mathSerivce->calculateEuler(convolvedResult.sum, 1);

                    timeVector.push_back(fequenceA);
                    bMatches.push_back(std::complex<double>(realA, imagA));          

                    if (/*realA > 0 && imagA > 0 &&*/ fequenceA > frequencMax)
                    {
                        bestHerz = herz;
                        bestA = a;
                        bestB = b*timeFactor;
                        bestWaveletOutput = waveletOutput;
                        bestConvolvedVector = convolvedResult.convolvedSignal;
                        frequencMax = fequenceA;
                
                        currentBest = true;
                    }
                }
            }
        }

        if (currentBest)
        {
            bestMatches.clear();

            for (int i = 0; i < bMatches.size(); i++)
            {
                bestMatches.push_back(bMatches[i]);
            }
        }

        bMatches.clear();
        
        frequenceTime.insert(std::pair<double, std::vector<double>>(herz, timeVector));
    }

    return WaveletResult(bestWaveletOutput, bestConvolvedVector, bestHerz, bestA, bestB, bestMatches, frequenceTime, maxHerz);
}

double MorletWaveletService::calculateWaveletFunctionOffset(double timeFactor, double omega0, double sigma, double a, double tollerance)
{
    if (isinf(a))
    {
        return 0;
    }

    std::complex<double> lastOutput = 0;

    for (int offset = 0; offset < 99999; offset++)
    {
        //double part = (t - waveletSize / 2.0);
        double time = offset * timeFactor;

        std::complex<double> output = this->calculateWaveletFunction((time / a), omega0, sigma);
        
        if (abs(output.real()) < tollerance && abs(output.imag()) < tollerance && abs(lastOutput.real()) < tollerance && abs(lastOutput.imag()) < tollerance)
        {
            return offset;
        }

        lastOutput = output;
    }
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
        result += (signal[i] * wavelet[i]);
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