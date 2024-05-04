#ifndef IPrimitiveDraw_H
#define IPrimitiveDraw_H

#include "IGeometry.h"
#include "IPrimitiveGraphic.h"

class IPrimitiveDraw
{
public:
	virtual void render(IPrimitiveGraphic* graphicEngine, IGeometry* facet) = 0;
};

#endif