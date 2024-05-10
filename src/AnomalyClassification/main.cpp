// AnomalyClassification.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
//
#include <iostream>
#include <string>

#include "GraphicEngineExtended.h"
#include "MyEventReceiver.h"
#include "SuperPixelService.h"
#include "ColorService.h"
#include "StringSerivce.h"

void superPixelToImage(std::vector<std::vector<SuperPixelEntry>> pixelCluster, int width, int height)
{
    const unsigned int size_z = 1;
    const unsigned int size_c = 3;

    CImg<unsigned int> bg(width, height, size_z, size_c, 255);

    for (int k = 0; k < pixelCluster.size(); k++)
    {
        const unsigned char(&color)[3] = { (unsigned char)(k * 75), (unsigned char)(k * 75), (unsigned char)(k * 75) };

        for (int i = 0; i < pixelCluster[k].size(); i++)
        {
            SuperPixelEntry entry = pixelCluster[k][i];
            bg.draw_point(entry.position.x, entry.position.y, color);
        }
    }

    bg.save_png("temp.png");
}

int main()
{

    StringSerivce stringSerivce;
    ColorService colorService;
    MathSerivce mathSerivce;
    SuperPixelService superPixelService(&colorService, &mathSerivce);

    std::wstring wFile = L"..\\AnomalyGeneration\\testdata\\defect\\75.png";
    std::string cFile = stringSerivce.toString(wFile);

    CImg<unsigned char> img(cFile.c_str());
    SubregionResult result = superPixelService.calculateSuperPixelsAndSubregions(img, 50);

    superPixelToImage(result.subregions, img.width(), img.height());

    GraphicEngineExtended graphicEngine(&stringSerivce);
    MyEventReceiver receiver(&graphicEngine);

    graphicEngine.initiate(L"Part Cover", Point2D(640, 480));
    graphicEngine.loadFont(L"fonthaettenschweiler.bmp");

    graphicEngine.addImage(0, Point2D(200, 200), L"temp.png");

    graphicEngine.addImage(GUI_ID_IMAGE, Point2D(10, 10), wFile.c_str());

    graphicEngine.run((EventReceiver*)&receiver);
}