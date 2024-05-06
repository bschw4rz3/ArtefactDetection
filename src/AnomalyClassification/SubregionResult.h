#ifndef SubregionResult_H
#define SubregionResult_H

#include "SuperPixelResult.h"

class SubregionResult : SuperPixelResult
{
public:
	SubregionResult(std::vector<SuperPixelEntry> clusterCenters, std::vector<std::vector<SuperPixelEntry>> superPixelClusters) : SuperPixelResult(clusterCenters, superPixelClusters)
	{

	}

};

#endif