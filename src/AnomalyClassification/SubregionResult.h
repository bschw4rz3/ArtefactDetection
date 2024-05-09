#ifndef SubregionResult_H
#define SubregionResult_H

#include "SuperPixelResult.h"

class SubregionResult : public SuperPixelResult
{
public:
	std::vector<std::vector<SuperPixelEntry>> subregions;

public:
	SubregionResult(std::vector<SuperPixelEntry> clusterCenters, std::vector<std::vector<SuperPixelEntry>> superPixelClusters, std::vector<std::vector<SuperPixelEntry>> subregions) : SuperPixelResult(clusterCenters, superPixelClusters)
	{
		this->subregions = subregions;
	}

};

#endif