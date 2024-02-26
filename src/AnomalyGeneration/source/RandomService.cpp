#include "../header/RandomService.h"

int RandomService::random(int steuerung, double pixelDistribution)
{
    if (steuerung == 0)
    {
        return 0;
    }

    double random = std::rand();
    double scaledRandom = random / ((RAND_MAX + 1u) / 2) - (1);

    double o = sqrt(sqrt(pixelDistribution));
    double x = scaledRandom;

    double result = x;
    result = round(pow(x, pixelDistribution) * pow(x, pixelDistribution) * x * (steuerung / 2));

    return result;
}

double RandomService::randomOneScaled()
{
    double random = std::rand();
    double result = random / (RAND_MAX + 1u);
    return result;
}