#include "BiorWavletService.h"

BiorWavletService::BiorWavletService()
{
}

// Funktion zur Berechnung der skalierten und verschobenen Wavelet-Funktion
std::vector<double> BiorWavletService::generateWavelet(const std::vector<double>& wavelet, double scale, double translation, int signalSize) 
{
    std::vector<double> scaledWavelet(signalSize, 0.0);
    int M = wavelet.size();

    // Skaliere und verschiebe die Wavelet-Funktion
    for (int i = 0; i < signalSize; ++i) {
        double t = (i - translation) / scale;
        int index = static_cast<int>(t);
        
        if (index >= 0 && index < M) {
            scaledWavelet[i] = wavelet[index] / sqrt(scale);  // Normierung der Wavelet-Funktion
        }
    }
    
    return scaledWavelet;
}

// Funktion zur Berechnung der Wavelet-Transformation (Bior Wavelet)
std::map<double, std::vector<std::complex<double>>> BiorWavletService::biorWaveletTransform(const std::vector<std::complex<double>>& input, const std::vector<double>& wavelet, int scaleSteps, int translationSteps)
{
    // Matrix für das Ergebnis (2D)
    std::map<double, std::vector<std::complex<double>>> result2D;

    int N = input.size();
    
    // Durchlaufen der Skalen (a) und der Verschiebungen (b)
    for (int a = 1; a <= scaleSteps; ++a) {
        double scaleFactor = pow(2.0, a); // Dyadische Skalierung (z.B. 2^a)
        
        std::vector<std::complex<double>> line(translationSteps, 0.0);
        result2D.insert(std::pair<double, std::vector<std::complex<double>>>(a, line));

        for (int b = 0; b < translationSteps; ++b) {
            double sum = 0.0;

            // Erzeuge die skalierte und verschobene Wavelet-Funktion
            std::vector<double> scaledWavelet = this->generateWavelet(wavelet, scaleFactor, b, N);

            // Berechne die Konvolution des skalierten Wavelets mit dem Eingangssignal
            for (int n = 0; n < N; ++n) {
                sum += std::abs(input[n]) * scaledWavelet[n];  // Betragsbildung der komplexen Zahlen
            }
            
            // Speichere das Ergebnis in der Matrix
            result2D[a][b] = sum;
        }
    }
    
    return result2D;
}

// Beispiel für Bior-Wavelet-Koeffizienten (Dummy-Werte)
std::vector<double> BiorWavletService::biorWaveletCoefficients() {
    return {0.0, 0.4829629131445341, 0.8365163037378079, 0.2241438680420134, -0.1294095225512604}; // Dummy-Werte für Bior-Wavelet
}

std::map<double, std::vector<std::complex<double>>> BiorWavletService::calculate(std::vector<std::complex<double>> input, int scaleSteps) 
{
    // Lade die Wavelet-Koeffizienten
    std::vector<double> wavelet = biorWaveletCoefficients();
    
    // Anzahl der Skalen und Verschiebungen, die durchprobiert werden sollen
    int translationSteps = input.size();  // Anzahl der Zeitverschiebungsschritte
    
    // Berechne die Bior Wavelet Transformation
    return this->biorWaveletTransform(input, wavelet, scaleSteps, translationSteps);
}