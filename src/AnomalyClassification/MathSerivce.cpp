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

    double factor = pow(digit, 2);
    return round(value * factor)/ factor;
}