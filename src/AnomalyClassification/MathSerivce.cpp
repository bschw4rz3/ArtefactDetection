#include "MathSerivce.h"

double MathSerivce::degreesToRadians(double degrees) {
    return degrees * (M_PI / 180.0);
}

double MathSerivce::sinDegrees(double degreeAngel)
{
    double radAngel = this->degreesToRadians(degreeAngel);
    return sin(radAngel);
}

double MathSerivce::roundDigits(double value, int digit)
{
    double factor = pow(digit, 2);
    return round(value * factor)/ factor;
}