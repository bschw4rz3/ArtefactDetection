#ifndef SuperPixelResult_H
#define SuperPixelResult_H

#include <vector>

#include "SuperPixelEntry.h"

class SuperPixelResult
{
public:
	std::vector<SuperPixelEntry> clusterCenters;

	std::vector<std::vector<SuperPixelEntry>> superPixelClusters;

	SuperPixelResult(std::vector<SuperPixelEntry> clusterCenters, std::vector<std::vector<SuperPixelEntry>> superPixelClusters)
	{
		this->clusterCenters = clusterCenters;
		this->superPixelClusters = superPixelClusters;
	}
	
};

#endif