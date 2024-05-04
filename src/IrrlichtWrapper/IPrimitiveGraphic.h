#ifndef IPrimitiveGraphic_H
#define IPrimitiveGraphic_H

#include "Point2D.h"
#include "Color.h"

class IPrimitiveGraphic
{
public:
    virtual void add2DLine(Point2D one, Point2D two, Color color) = 0;
    virtual void add2DPixel(Point2D position, Color color) = 0;
    virtual void add2DRectangle(Point2D from, Point2D to, Color color) = 0;
    virtual void addImage(Point2D position, const wchar_t* file) = 0;
};

#endif