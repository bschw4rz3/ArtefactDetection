#include "MathSerivce.h"

double MathSerivce::degreesToRadians(double degrees) {
    return degrees * (M_PI / 180.0);
}

double MathSerivce::radiansToDegrees(double radiant) {
    return radiant * (180.0/M_PI);
}

double MathSerivce::sinDegrees(double degreeAngel)
{
    double radAngel = this->degreesToRadians(degreeAngel);
    return sin(radAngel);
}

double MathSerivce::cosDegrees(double degreeAngel)
{
    double radAngel = this->degreesToRadians(degreeAngel);
    return cos(radAngel);
}

double MathSerivce::atanDegrees(double value)
{
    double result = atan(value);

    return this->radiansToDegrees(result);
}

double MathSerivce::roundDigits(double value, int digit)
{
    if(digit <= 0)
    {
        return round(value);
    }

    double factor = pow(10, digit);
    return round(value * factor)/ factor;
}

double MathSerivce::calculateEuler(std::complex<double> time, double w_0)
{
    return this->sinDegrees(w_0 * time.real()) + this->cosDegrees(w_0 * time.imag());
}

long double MathSerivce::avg(std::vector<double> v)
{
    long double firstResult = 0;
    long double secondResult = 0;

    long long size = v.size();

    for(int i = 0 ; i < size ; i++)
    {
        firstResult += v[i] / size;
        secondResult += ((long) v[i]) % size;
    }

    return firstResult + (secondResult/size);
    
}

long double MathSerivce::calculateSkewness(std::vector<double> data)
{
    double mean = this->avg(data);
    double stddev = this->calculateStandardDeviation(data, mean);

    double skewness = 0.0;
    for (double value : data) {
        skewness += std::pow((value - mean) / stddev, 3);
    }

    return skewness / data.size();
}

long double MathSerivce::calculateStandardDeviation(const std::vector<double>& data, double mean) {
    long double sum = 0.0;
    for (double value : data) {
        sum += std::pow(value - mean, 2);
    }
    return std::sqrt(sum / data.size());
}

long double MathSerivce::calculateVariance(const std::vector<double> data) {
    long double mean = this->avg(data);
    long double variance = 0.0;

    for (double value : data) {
        variance += std::pow(value - mean, 2);
    }

    return variance / data.size(); // Für Stichprobenvarianz statt N -> (N-1)
}

long double MathSerivce::calculateEnergy(const std::vector<double>& signal) {
    long double energy = 0.0;

    for (double value : signal) {
        energy += value * value; // Quadriere die Werte und summiere sie
    }

    return energy;
}

long double MathSerivce::calculateKurtosis(const std::vector<double> data) {
    double mean = this->avg(data);
    double variance = this->calculateVariance(data);

    if (variance == 0.0) {
        return 0.0; // Um Division durch Null zu vermeiden
    }

    double kurtosis = 0.0;
    for (double value : data) {
        kurtosis += std::pow((value - mean), 4);
    }

    kurtosis = (kurtosis / data.size()) / std::pow(variance, 2);

    return kurtosis;
}