#ifndef OrientationResult_H
#define OrientationResult_H

class OrientationResult
{
public:
    int height;
    int width;
    int angle;

public:
    OrientationResult(int width, int height, int angle)
    {
        this->width = width;
        this->height = height;
        this->angle = angle;
    }
};

#endif