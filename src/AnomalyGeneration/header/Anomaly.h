#ifndef Anomaly_H
#define Anomaly_H

#include "PixelPosition.h"

enum AnomalyType {
	MinorDefect,
	Defect,
	Artefact
};

class Anomaly
{
public:
	PixelPosition from;
	PixelPosition to;

	AnomalyType anomalyType;

	Anomaly(PixelPosition from, PixelPosition to, AnomalyType anomalyType) 
	{
		this->from = from;
		this->to = to;

		this->anomalyType = anomalyType;
	}
};

#endif