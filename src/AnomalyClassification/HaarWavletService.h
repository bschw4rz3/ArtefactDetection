#ifndef HaarWavletService_H
#define HaarWavletService_H

#include <iostream>
#include <vector>
#include <cmath>

#include "MorletWaveletServiceFFT.h"

class HaarWavletService : public MorletWaveletServiceFFT
{
public:
	HaarWavletService();

protected:
	virtual std::vector<std::complex<double>> waveletFunction(int n, double freq, double dt);

};

#endif