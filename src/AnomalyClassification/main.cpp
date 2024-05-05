// AnomalyClassification.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
//

#include <iostream>
#include <string>
#include "../IrrlichtWrapper/GraphicEngine.h"
#include "MyEventReceiver.h"
#include "SuperPixelService.h"
#include "ColorService.h"

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
    std::wstring file = L"..\\AnomalyGeneration\\testdata\\defect\\75.png";

    ColorService colorService;
    SuperPixelService superPixelService(&colorService);

    CImg<unsigned char> img("..\\AnomalyGeneration\\testdata\\defect\\75.png");
    std::vector<std::vector<SuperPixelEntry>> pixelCluster = superPixelService.process(50, img);

    superPixelToImage(pixelCluster, img.width(), img.height());

    GraphicEngine graphicEngine;
    MyEventReceiver receiver(&graphicEngine);

    graphicEngine.initiate(L"Part Cover", Point2D(640, 480));
    graphicEngine.loadFont(L"fonthaettenschweiler.bmp");

    graphicEngine.addImage(GUI_ID_IMAGE, Point2D(10, 10), file.c_str());

    graphicEngine.run((EventReceiver*)&receiver);
}