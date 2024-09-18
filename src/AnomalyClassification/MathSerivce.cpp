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