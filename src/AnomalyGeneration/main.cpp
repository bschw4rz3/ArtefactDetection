// main.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
//

#pragma warning(disable:4146)
#pragma warning(disable:4996)

#define cimg_use_png

#include <conio.h>
#include <direct.h>

#include <format>
#include <iostream>
#include <chrono>
#include <string> 
#include "header/cimg/CImg.h"
#include "header/DrawCalculations.h"
#include "header/RandomService.h"
#include "header/DrawBumpCalculations.h"
#include "header/Anomaly.h"

using namespace cimg_library;

bool contains(std::vector<Anomaly> list, AnomalyType type)
{
    for(int i = 0;i < list.size();i++)
    {
        if(list[i].anomalyType == type)
        {
            return true;
        }
    }

    return false;
}

int main()
{
    int w = 1000;
    int h = 800;

    std::vector<Anomaly> anomalyList;

    const unsigned char bluegreen[] = {0, 170, 255};
    const unsigned char black[] = {0, 0, 0};
    const unsigned char withe[] = {255, 255, 255};

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

    c.drawRectPart(&bg, PixelPosition(xPos, yPos), (w/2)-50, (h/2)-50, 10, 1, withe, black);
    
    int countOfAnomalies = randomService.randomFromTo(0,10);

    for(int i = 0;i<countOfAnomalies;i++)
    {
        double anomalyType = randomService.randomOneScaled();

        int positionX = randomService.randomFromTo(0,w);
        int positionY = randomService.randomFromTo(0,h);

        if(anomalyType < 0.5)
        {
            int size = randomService.randomFromTo(1,10);
            double pixelDistribution = randomService.randomFromTo(0,10);
            double pixelStreung = randomService.randomFromTo(0,2.0);

            PixelPosition position(positionX, positionY);
            std::vector<PixelPosition> pixels = c.drawLiddelRandomBumb(&bg, position, size, pixelStreung, pixelDistribution, black);
            anomalyList.push_back(Anomaly(pixels, AnomalyType::MinorDefect));
        }
        else if(anomalyType < 0.8)
        {
            PixelPosition positionFrom(positionX, positionY);
            
            positionX = randomService.randomFromTo(0,w);
            positionY = randomService.randomFromTo(0,h);

            PixelPosition positionTo(positionX, positionY);

            int brigth = randomService.randomFromTo(0,30);
            int countOfLines = randomService.randomFromTo(0,10);
            int pixelCount = randomService.randomFromTo(0,20000);

            std::vector<PixelPosition> pixels = c.drawScratch(&bg, positionFrom, positionTo, brigth, countOfLines, pixelCount, black);
            anomalyList.push_back(Anomaly(pixels, AnomalyType::Defect));
        }
        else if(anomalyType < 0.75)
        {
            int radius = randomService.randomFromTo(0,150);
            int rotationInterval = randomService.randomFromTo(0,50);
            double pixelStreuung = randomService.randomFromTo(0,50);
            double pixelCount = randomService.randomFromTo(0,10);
            double pixelDistribution = randomService.randomFromTo(0,10);
            double fadeFromTo = randomService.randomFromTo(0,1);
            double fadeOutY = randomService.randomFromTo(0,1);
            double rotation = randomService.randomFromTo(0,360);

            PixelPosition position(positionX, positionY);    
            
            std::vector<PixelPosition> pixels = c.drawMultipleCicelCloud(&bg, position, radius, rotationInterval, pixelStreuung, pixelCount, pixelDistribution, fadeFromTo, fadeOutY, rotation, black);
            anomalyList.push_back(Anomaly(pixels, AnomalyType::Artefact));
        }
        else if(anomalyType < 1.0)
        {
            int radius = randomService.randomFromTo(0,150);
            int rotationInterval = randomService.randomFromTo(0,50);
            double pixelStreuung = randomService.randomFromTo(0,20);
            double pixelCount = randomService.randomFromTo(0,10);
            double pixelDistribution = randomService.randomFromTo(0,10);
            double fadeFromTo = randomService.randomFromTo(0,1);
            double fadeOutY = randomService.randomFromTo(0,1);
            double rotation = randomService.randomFromTo(0,360);

            PixelPosition position(positionX, positionY);

            std::vector<PixelPosition> pixels = c.drawMultipleCicelCloud(&bg, position, radius, rotationInterval, pixelStreuung, pixelCount, pixelDistribution, fadeFromTo, fadeOutY, rotation, withe);
            Anomaly anomaly(pixels, AnomalyType::Artefact);
            
            PixelPosition from = anomaly.getFrom();
            PixelPosition to = anomaly.getTo();

            PixelPosition diff = to-from;
            double w = abs(diff.x / 2);
            double h = abs(diff.y / 2);
            PixelPosition rectPosition = from + diff;

            c.drawRect(&bg, rectPosition, w, h, black);
            c.drawMultipleCicelCloud(&bg, position, radius, rotationInterval, pixelStreuung, pixelCount, pixelDistribution, fadeFromTo, fadeOutY, rotation, withe);

            anomalyList.push_back(anomaly);
        }
    }

    bg.display();

    int wx = 200;
    int hy = 200;
    int index = 0;

    mkdir("testdata");
    mkdir("testdata/defect");
    mkdir("testdata/artefact");
    mkdir("testdata/none");

    for(int x = 0;x<w;x+=wx)
    {
        std::vector<AnomalyType> anomalyTypeList;

        for(int y = 0;y<h;y+=hy)
        {
            PixelPosition imageFrom(x, y);
            PixelPosition imageTo(x+wx-1, y+hy-1);

            CImg<unsigned char> tmp = bg.get_crop(imageFrom.x, imageFrom.y, 0, 0, imageTo.x, imageTo.y, 0, size_c);
            
            for(int i = 0;i<anomalyList.size();i++)
            {
                if(anomalyList[i].IsInImage(imageFrom, imageTo))
                {
                    anomalyTypeList.push_back(anomalyList[i].anomalyType);
                }
            }

            std::string path = "testdata/";

            if(contains(anomalyList, AnomalyType::Defect) || contains(anomalyList, AnomalyType::MinorDefect))
            {
                path = path + "defect/";
            }
            else if(contains(anomalyList, AnomalyType::Artefact))
            {
                path = path + "artefact/";
            }
            else
            {
                path = path + "none/";
            }

            std::string complitePath = path + std::to_string(index) + ".png";
            FILE* file = std::fopen(complitePath.c_str(), "r");

            while(file != NULL)
            {
                fclose(file);

                index++;
                complitePath = path + std::to_string(index) + ".png";

                file = fopen(complitePath.c_str(), "r");
            }
            
            file = std::fopen(complitePath.c_str(), "wb");

            unsigned char* buffer = tmp.data();

            CImg<unsigned char> tmpSave = CImg<unsigned char>(buffer, wx, hy, size_z, size_c, 255);
            tmpSave.display();
            tmpSave.save_png(file);

            fclose(file);
        }
    }    
}