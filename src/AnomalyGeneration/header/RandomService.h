#ifndef RandomService_h
#define RandomService_h

#include <iostream>
#include <random>
#include <iostream> 
#include <cstdlib> 
#include <ctime> 

using namespace std;

class RandomService {

public:
	int random(int steuerung, double pixelDistribution);
	double randomFromTo(double from, double to);

	double randomOneScaled();
	double randomOnePosAndNegScaled();
};

#endif