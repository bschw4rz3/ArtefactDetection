#ifndef Anomaly_H
#define Anomaly_H

#include <algorithm>
#include <iostream>
#include <vector>

#include "PixelPosition.h"

enum AnomalyType {
	MinorDefect,
	Defect,
	Artefact
};

class Anomaly
{
public:
	AnomalyType anomalyType;
	std::vector<PixelPosition> pixelList;
	
public:
	Anomaly(std::vector<PixelPosition> pixels, AnomalyType anomalyType);

	PixelPosition getFrom();
	PixelPosition getTo();

	bool IsInImage(PixelPosition imageFrom, PixelPosition imageTo);

private:
	int getMaxX();
	int getMaxY();
	int getMinX();
	int getMinY();
};

#endif