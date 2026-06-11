#include "DiscreteFourierTransformationSerivceCV.h"

std::vector<double> DiscreteFourierTransformationSerivceCV::calculateRadialProfile(const cv::Mat& magnitudeImage) 
{
    int centerX = magnitudeImage.cols / 2;
    int centerY = magnitudeImage.rows / 2;

    // Maximaler Radius ist der Abstand von der Bildmitte zur Ecke
    int maxRadius = std::sqrt(centerX * centerX + centerY * centerY);
    std::vector<double> radialProfile(maxRadius, 0.0f);
    std::vector<int> radialCount(maxRadius, 0);

    // Iteriere über jedes Pixel und sammle Werte nach Radius
    for (int y = 0; y < magnitudeImage.rows; ++y) {
        for (int x = 0; x < magnitudeImage.cols; ++x) {
            int dx = x - centerX;
            int dy = y - centerY;
            int radius = static_cast<int>(std::sqrt(dx * dx + dy * dy));
            if (radius < maxRadius) {

                float value = magnitudeImage.at<float>(y, x);

                radialProfile[radius] += value;
                radialCount[radius] += 1;
            }
        }
    }

    // Mittelwert des Profils berechnen
    for (int i = 0; i < maxRadius; ++i) {
        if (radialCount[i] > 0) {
            radialProfile[i] /= radialCount[i];
        }
    }

    return radialProfile;
}

std::vector<double> DiscreteFourierTransformationSerivceCV::calculateFrequencies(int maxRadius, int width, int height, double samplingRate) {
    std::vector<double> frequencies(maxRadius);
    float freqPerPixelX = samplingRate / width;  // Frequenz pro Pixel in x-Richtung
    float freqPerPixelY = samplingRate / height; // Frequenz pro Pixel in y-Richtung

    for (int r = 0; r < maxRadius; ++r) {
        float radiusX = static_cast<float>(r) / (width / 2.0f);
        float radiusY = static_cast<float>(r) / (height / 2.0f);
        frequencies[r] = std::sqrt((radiusX * freqPerPixelX) * (radiusX * freqPerPixelX) +
            (radiusY * freqPerPixelY) * (radiusY * freqPerPixelY));
    }

    return frequencies;
}

DFTResult DiscreteFourierTransformationSerivceCV::calculate(std::string filename)
{
    DFTResult result;

    Mat I = imread(filename, IMREAD_GRAYSCALE);
    if (I.empty())
        return result;

    Mat padded;                            //expand input image to optimal size
    int m = getOptimalDFTSize(I.rows);
    int n = getOptimalDFTSize(I.cols); // on the border add zero values
    copyMakeBorder(I, padded, 0, m - I.rows, 0, n - I.cols, BORDER_CONSTANT, Scalar::all(0));

    Mat planes[] = { Mat_<float>(padded), Mat::zeros(padded.size(), CV_32F) };
    Mat complexI;
    merge(planes, 2, complexI);         // Add to the expanded another plane with zeros

    dft(complexI, complexI);            // this way the result may fit in the source matrix

    // compute the magnitude and switch to logarithmic scale
    // => log(1 + sqrt(Re(DFT(I))^2 + Im(DFT(I))^2))
    split(complexI, planes);                   // planes[0] = Re(DFT(I), planes[1] = Im(DFT(I))
    magnitude(planes[0], planes[1], planes[0]);// planes[0] = magnitude
    Mat magI = planes[0];

    magI += Scalar::all(1);                    // switch to logarithmic scale
    log(magI, magI);

    // crop the spectrum, if it has an odd number of rows or columns
    magI = magI(Rect(0, 0, magI.cols & -2, magI.rows & -2));

    // rearrange the quadrants of Fourier image  so that the origin is at the image center
    int cx = magI.cols / 2;
    int cy = magI.rows / 2;

    Mat q0(magI, Rect(0, 0, cx, cy));   // Top-Left - Create a ROI per quadrant
    Mat q1(magI, Rect(cx, 0, cx, cy));  // Top-Right
    Mat q2(magI, Rect(0, cy, cx, cy));  // Bottom-Left
    Mat q3(magI, Rect(cx, cy, cx, cy)); // Bottom-Right

    Mat tmp;                           // swap quadrants (Top-Left with Bottom-Right)
    q0.copyTo(tmp);
    q3.copyTo(q0);
    tmp.copyTo(q3);

    q1.copyTo(tmp);                    // swap quadrant (Top-Right with Bottom-Left)
    q2.copyTo(q1);
    tmp.copyTo(q2);

    normalize(magI, magI, 0, 1, NORM_MINMAX); // Transform the matrix with float values into a
    // viewable image form (float between values 0 and 1).

    result.spectrumMagnitude = magI;
    std::vector<double> radialProfile = this->calculateRadialProfile(magI);
    result.radialProfile = radialProfile;
    
    result.frequencies = this->calculateFrequencies(radialProfile.size(), magI.rows, magI.cols, 1);
    

    return result;
}