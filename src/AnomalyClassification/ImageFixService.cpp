#include "ImageFixService.h"

ImageFixService::ImageFixService(GeometricService* geometricService, ColorService* colorService, TempFileNameService* tempFileNameService)
{
    this->geometricService = geometricService;
    this->colorService = colorService;
    this->tempFileNameService = tempFileNameService;
}

void ImageFixService::fixImage(CImg<unsigned char>* img, std::string outFileName)
{
    const unsigned char white[] = { 255,255,255 };
    std::vector<Point2D> borderPositions = this->getPartBorders(img);

    const unsigned int size_z = 1;
    const unsigned int size_c = 3;

    CImg<unsigned char> sizeImg(*img);

    sizeImg.resize(sizeImg.width() + 1, sizeImg.height() + 1, size_z, size_c, 0);

    for (int i = 0; i < borderPositions.size(); i++)
    {
        for (int j = 0; j < borderPositions.size(); j++)
        {
            for (int h = 0; h < borderPositions.size(); h++)
            {
                sizeImg.draw_triangle(borderPositions[i].x, borderPositions[i].y, borderPositions[j].x, borderPositions[j].y, borderPositions[h].x, borderPositions[h].y, white, white, white, 1.0);
            }
        }
    }

    if (img->width() >= 600 || img->height() >= 600)
    {
        sizeImg = sizeImg.resize_halfXY();
    }

    sizeImg.draw_line(sizeImg.width() - 1, 0, sizeImg.width() - 1, sizeImg.height() - 1, white);
    sizeImg.draw_line(0, sizeImg.height() - 1, sizeImg.width() - 1, sizeImg.height() - 1, white);

    sizeImg.resize(600, 600, -100, -100, 0, 1, 0, 0, 0, 0);
    sizeImg.save_png(outFileName.c_str());
}

std::vector<Point2D> ImageFixService::getPartBorders(CImg<unsigned char>* img)
{
    BackgroundResult backgroundColorList = this->geometricService->getBackgroundList(img);
    std::vector<Point2D> backPixelPositions;
    std::vector<Point2D> positionList;

    for (int i = 0; i < backgroundColorList.colorList.size(); i++)
    {
        ColorRGB color = backgroundColorList.colorList[i];

        if (color.r == 0)
        {
            backPixelPositions.push_back(backgroundColorList.pointList[i]);
        }
    }

    if (backPixelPositions.size() > 0)
    {
        std::vector<Point2D> fromPosition({ Point2D(0, 0),           Point2D(0, 0),             Point2D(0, img->height() - 1),          Point2D(img->width() - 1, 0) });
        std::vector<Point2D> toPosition({ Point2D(1, img->height()), Point2D(img->width(), 1),  Point2D(img->width(), img->height()), Point2D(img->width(), img->height()) });

        for (int i = 0; i < fromPosition.size(); i++)
        {
            const unsigned char* bytePixel = img->data(fromPosition[i].x, fromPosition[i].y);
            ColorRGB lastColor = this->colorService->byte2rgb(bytePixel, img->width(), img->height());

            std::vector<Point2D> positionsLine;

            for (int x = fromPosition[i].x; x < toPosition[i].x; x++)
            {
                for (int y = fromPosition[i].y; y < toPosition[i].y; y++)
                {
                    const unsigned char* bytePixel = img->data(x, y);
                    ColorRGB color = this->colorService->byte2rgb(bytePixel, img->width(), img->height());

                    if (color != lastColor)
                    {
                        positionsLine.push_back(Point2D(x, y));
                    }

                    lastColor = color;
                }
            }

            if (positionsLine.size() > 0)
            {
                long positionX = 0;
                long positionY = 0;

                for (int i = 0; i < positionsLine.size(); i++)
                {
                    positionX += positionsLine[i].x;
                    positionY += positionsLine[i].y;
                }

                positionX /= positionsLine.size();
                positionY /= positionsLine.size();

                positionList.push_back(Point2D(positionX, positionY));
            }
        }
    }

    for (int i = 0 ; i < backPixelPositions.size(); i++)
    {
        positionList.push_back(backPixelPositions[i]);
    }

    return positionList;
}