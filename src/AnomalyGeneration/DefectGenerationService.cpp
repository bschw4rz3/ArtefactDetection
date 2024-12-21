#include "DefectGenerationService.h"

bool DefectGenerationService::contains(std::vector<AnomalyType> list, AnomalyType type)
{
    for(int i = 0;i < list.size();i++)
    {
        if(list[i] == type)
        {
            return true;
        }
    }

    return false;
}

bool DefectGenerationService::containsWithePixels(CImg<unsigned char> &tmp)
{
    for (int x = 0; x < tmp.width(); x++)
    {
        for (int y = 0; y < tmp.height(); y++)
        {
            unsigned char currentColor = tmp._data[y * tmp.width() + x];

            if (currentColor == 0)
            {
                return true;
            }
        }
    }

    return false;
}

std::string DefectGenerationService::getTestdataImagePath(std::vector<AnomalyType> anomalyTypeList, int index, std::string path)
{
    if (contains(anomalyTypeList, AnomalyType::Defect) || contains(anomalyTypeList, AnomalyType::MinorDefect))
    {
        path = path + "/defect/";
    }
    else if (contains(anomalyTypeList, AnomalyType::Artefact))
    {
        path = path + "/artefact/";
    }
    else
    {
        path = path + "/none/";
    }

    return path + std::to_string(index) + ".png";
}

std::string DefectGenerationService::saveImage(CImg<unsigned char>& tmp, int wx, int hy, int size_z, int size_c, std::vector<AnomalyType>& anomalyTypeList, int& index, std::string dirPath)
{
    std::string complitePath = this->getTestdataImagePath(anomalyTypeList, index, dirPath);
    FILE* file = std::fopen(complitePath.c_str(), "r");

    while (file != NULL)
    {
        fclose(file);

        index++;
        complitePath = this->getTestdataImagePath(anomalyTypeList, index, dirPath);

        file = fopen(complitePath.c_str(), "r");
    }

    file = std::fopen(complitePath.c_str(), "wb");

    unsigned char* buffer = tmp.data();

    CImg<unsigned char> tmpSave = CImg<unsigned char>(buffer, wx, hy, size_z, size_c, 255);
    //tmpSave.display();
    tmpSave.save_png(file);

    fclose(file);

    return complitePath;
}

void DefectGenerationService::cutSubPics(CImg<unsigned int>& bg, std::vector<Anomaly>& anomalyList, int w, int h, int size_z, int size_c, std::string dirPath)
{
    int wx = 200;
    int hy = 200;
    int index = 0;

    for (int x = 0; x < w; x += wx)
    {
        std::vector<AnomalyType> anomalyTypeList;

        for (int y = 0; y < h; y += hy)
        {
            PixelPosition imageFrom(x, y);
            PixelPosition imageTo(x + wx - 1, y + hy - 1);

            CImg<unsigned char> tmp = bg.get_crop(imageFrom.x, imageFrom.y, 0, 0, imageTo.x, imageTo.y, 0, size_c);

            for (int i = 0; i < anomalyList.size(); i++)
            {
                if (anomalyList[i].IsInImage(imageFrom, imageTo))
                {
                    anomalyTypeList.push_back(anomalyList[i].anomalyType);
                }
            }

            if (!containsWithePixels(tmp))
            {
                continue;
            }

            saveImage(tmp, wx, hy, size_z, size_c, anomalyTypeList, index, dirPath);
        }
    }
}

void DefectGenerationService::cutAnomalies(CImg<unsigned int>& bg, std::vector<Anomaly>& anomalyList, int w, int h, int size_z, int size_c, std::string dirPath)
{
    int index = 0;

    for (int i = 0; i < anomalyList.size(); i++)
    {
        PixelPosition from = anomalyList[i].getFrom();
        PixelPosition to = anomalyList[i].getTo();

        if (anomalyList[i].pixelList.size() == 0)
        {
            continue;
        }

        CImg<unsigned char> tmp = bg.get_crop(from.x, from.y, 0, 0, to.x, to.y, 0, size_c);

        std::vector<AnomalyType> anomalyTypeList;
        anomalyTypeList.push_back(anomalyList[i].anomalyType);

        saveImage(tmp, tmp.width(), tmp.height(), size_z, size_c, anomalyTypeList, index, dirPath);
    }
}

void DefectGenerationService::cutAnomaliesWithSize(CImg<unsigned int>& bg, std::vector<Anomaly>& anomalyList, int size_z, int size_c, int cutImageSize, std::string dirPath)
{
    int index = 0;

    for (int i = 0; i < anomalyList.size(); i++)
    {
        PixelPosition from = anomalyList[i].getFrom();
        PixelPosition to = anomalyList[i].getTo();

        if (abs(to.x - from.x) > cutImageSize || abs(to.y - from.y) > cutImageSize || from.x < 0 || from.y < 0)
        {
            continue;
        }

        double restX = cutImageSize - abs(to.x - from.x);
        double restY = cutImageSize - abs(to.y - from.y);

        RandomService randomService;

        double rX = (600.0 - (to.x - from.x));

        if (rX > from.x)
            rX = 0;

        double rY = (600.0 - (to.y - from.y));

        if (rY > from.y)
            rY = 0;

        double dX = rX * randomService.randomOneScaled();
        double dY = rY * randomService.randomOneScaled();

        double fX = from.x - dX;
        double fY = from.y - dY;
        double tX = (600 - dX - (to.x - from.x)) + to.x -1;
        double tY = (600 - dY - (to.y - from.y)) + to.y -1;

        CImg<unsigned char> tmp = bg.get_crop(fX, fY, 0, 0, tX, tY, 0, size_c);

        std::vector<AnomalyType> anomalyTypeList;
        anomalyTypeList.push_back(anomalyList[i].anomalyType);

        std::string imageFileName = saveImage(tmp, tmp.width(), tmp.height(), size_z, size_c, anomalyTypeList, index, dirPath);
        std::string textFileName = std::regex_replace(imageFileName, std::regex(".png"), ".txt");

        double percentStartX = (100.0 / ((double)cutImageSize) * dX) / 100.0;
        double percentStartY = (100.0 / ((double)cutImageSize) * dY) / 100.0;
        double percentToX = (1.0 - ((100.0 / ((double)cutImageSize) * (600 - dX - (to.x - from.x))) / 100.0))*2;
        double percentToY = (1.0 - ((100.0 / ((double)cutImageSize) * (600 - dY - (to.y - from.y))) / 100.0)) * 2;

        int type = 0;

        if (anomalyList[i].anomalyType == AnomalyType::Artefact)
        {
            type = 1;
        }

        std::ofstream myfile;
        myfile.open(textFileName);
        myfile << type;
        myfile << " " + std::to_string(percentStartX);
        myfile << " " + std::to_string(percentStartY);
        myfile << " " + std::to_string(percentToX);
        myfile << " " + std::to_string(percentToY);
        myfile.close();
    }
}

void DefectGenerationService::generateAnomalieDirectories(std::string dirPath, int iterationCount, int countOfAnomalies, int cutImageSize)
{
    int w = 1000;
    int h = 800;

    std::vector<Anomaly> anomalyList;

    const unsigned char bluegreen[] = {0, 170, 255};
    const unsigned char black[] = {0, 0, 0};
    const unsigned char withe[] = { 255, 255, 255 };

    const unsigned int size_z = 1;
    const unsigned int size_c = 3;

    CImg<unsigned int> bg(w, h, size_z, size_c, 255);

    bg.draw_rectangle(0, 0, w, h, black, 1);

    int xPos = w/2;
    int yPos = h/2;

    int r = 150;
    
    RandomService randomService;

    CalculationService calculationService;
    DrawCircelCalculations drawCircelCalculations(&calculationService, &randomService);
    DrawBumpCalculations drawBumpCalculations(&randomService);
    DrawCalculations c(&drawCircelCalculations, &drawBumpCalculations);

    mkdir(dirPath.c_str());
    mkdir((dirPath + "/defect").c_str());
    mkdir((dirPath + "/artefact").c_str());
    mkdir((dirPath + "/none").c_str());
    
    for (int j = 0; j < iterationCount; j++)
    {
        c.drawRectPart(&bg, PixelPosition(xPos, yPos), (w / 2) - 50, (h / 2) - 50, 10, 1, withe, black);

        if (countOfAnomalies == -1)
            countOfAnomalies = randomService.randomFromTo(0, 10);

        for (int i = 0; i < countOfAnomalies; i++)
        {
            double anomalyType = randomService.randomOneScaled();

            int positionX = randomService.randomFromTo(0, w);
            int positionY = randomService.randomFromTo(0, h);

            if (anomalyType < 0.25)
            {
                int size = randomService.randomFromTo(1, 10);
                double pixelDistribution = randomService.randomFromTo(0, 10);
                double pixelStreung = randomService.randomFromTo(0, 2.0);

                PixelPosition position(positionX, positionY);
                std::vector<PixelPosition> pixels = c.drawLiddelRandomBumb(&bg, position, size, pixelStreung, pixelDistribution, black);

                if (pixels.size() >= 8)
                {
                    anomalyList.push_back(Anomaly(pixels, AnomalyType::MinorDefect));
                }
            }
            else if (anomalyType < 0.5)
            {
                PixelPosition positionFrom(positionX, positionY);

                positionX = randomService.randomFromTo(0, w);
                positionY = randomService.randomFromTo(0, h);

                PixelPosition positionTo(positionX, positionY);

                int brigth = randomService.randomFromTo(0, 30);
                int countOfLines = randomService.randomFromTo(0, 10);
                int pixelCount = randomService.randomFromTo(0, 20000);

                std::vector<PixelPosition> pixels = c.drawScratch(&bg, positionFrom, positionTo, brigth, countOfLines, pixelCount, black);

                if (pixels.size() >= 8)
                {
                    anomalyList.push_back(Anomaly(pixels, AnomalyType::Defect));
                }
            }
            else if (anomalyType < 0.75)
            {
                int radius = randomService.randomFromTo(0, 150);
                int rotationInterval = randomService.randomFromTo(1, 50);
                double pixelStreuung = randomService.randomFromTo(0, 50);
                double pixelCount = randomService.randomFromTo(0, 10);
                double pixelDistribution = randomService.randomFromTo(0, 10);
                double fadeFromTo = randomService.randomFromTo(0, 1);
                double fadeOutY = randomService.randomFromTo(0, 1);
                double rotation = randomService.randomFromTo(0, 360);

                PixelPosition position(positionX, positionY);

                std::vector<PixelPosition> pixels = c.drawMultipleCicelCloud(&bg, position, radius, rotationInterval, pixelStreuung, pixelCount, pixelDistribution, fadeFromTo, fadeOutY, rotation, black);

                if (pixels.size() >= 8)
                {
                    anomalyList.push_back(Anomaly(pixels, AnomalyType::Artefact));
                }
            }
            else if (anomalyType < 1.0)
            {
                int radius = randomService.randomFromTo(0, 150);
                int rotationInterval = randomService.randomFromTo(1, 50);
                double pixelStreuung = randomService.randomFromTo(0, 20);
                double pixelCount = randomService.randomFromTo(0, 10);
                double pixelDistribution = randomService.randomFromTo(0, 10);
                double fadeFromTo = randomService.randomFromTo(0, 1);
                double fadeOutY = randomService.randomFromTo(0, 1);
                double rotation = randomService.randomFromTo(0, 360);

                PixelPosition position(positionX, positionY);

                std::vector<PixelPosition> pixels = c.drawMultipleCicelCloud(NULL, position, radius, rotationInterval, pixelStreuung, pixelCount, pixelDistribution, fadeFromTo, fadeOutY, rotation, withe);
                Anomaly anomaly(pixels, AnomalyType::Artefact);

                PixelPosition from = anomaly.getFrom();
                PixelPosition to = anomaly.getTo();

                PixelPosition diff = to - from;
                double w = abs(diff.x / 2);
                double h = abs(diff.y / 2);
                PixelPosition rectPosition(from.x + w, from.y + h);

                c.drawRect(&bg, rectPosition, w, h, black);
                c.drawPixelList(&bg, pixels, withe);

                if (pixels.size() >= 8)
                {
                    anomalyList.push_back(Anomaly(pixels, AnomalyType::Artefact));
                }
            }
        }

        //bg.display();

        if (cutImageSize == -1)
        {
            this->cutAnomalies(bg, anomalyList, w, h, size_z, size_c, dirPath);
        }
        else
        {
            this->cutAnomaliesWithSize(bg, anomalyList, size_z, size_c, cutImageSize, dirPath);
        }
    }
}