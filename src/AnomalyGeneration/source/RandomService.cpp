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

    double powX = pow(abs(x), pixelDistribution);
    result = powX * powX *x;

    double scaledResult = round(result*(((double)steuerung)/2));

    return scaledResult;
}

double RandomService::randomFromTo(double from, double to)
{
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(from, to);

    return dist(mt);
}

double RandomService::randomOneScaled()
{
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(0.0, 1.0);

    return dist(mt);
}

double RandomService::randomOnePosAndNegScaled()
{
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(-1.0, 1.0);

    return dist(mt);
}