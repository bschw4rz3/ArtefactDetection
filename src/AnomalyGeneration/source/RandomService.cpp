#include "../header/RandomService.h"

int RandomService::random(int steuerung, double pixelDistribution)
{
    if (steuerung == 0)
    {
        return 0;
    }

    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(-steuerung/2, steuerung/2);

    double scaledRandom = dist(mt);

    double o = sqrt(sqrt(pixelDistribution));
    double x = scaledRandom/(((double)steuerung)/2);

    double result = x;
    result = round(pow(x, pixelDistribution)*pow(x, pixelDistribution)*x*(((double)steuerung)/2));

    return result;
}

double RandomService::randomOneScaled()
{
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(0.0, 1.0);

    return dist(mt);
}