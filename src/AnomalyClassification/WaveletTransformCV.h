#ifndef WaveletTransformCV_H
#define WaveletTransformCV_H

#include <opencv2\highgui\highgui.hpp>
#include <opencv2\core\core.hpp>
#include <opencv2\core\mat.hpp>
#include <opencv2\imgproc\imgproc.hpp>

#include <iostream>
#include <string>
#include <sstream>

#include "StringSerivce.h"

using namespace std;
using namespace cv;

class WaveletTransformCV
{
private:
    static const unsigned int NUM_ROWS = 256;
    static const unsigned int NUM_COLS = NUM_ROWS;
    static const unsigned long NUM_PIXELS = NUM_COLS * NUM_ROWS;
    const float SQRT_2 = 1.414214f;

    StringSerivce* stringSerivce;

public:
    WaveletTransformCV(StringSerivce* stringSerivce);

    void calculate(std::string imagePath);

private:
    unsigned char validateLength(unsigned short* pI, unsigned int length);
    unsigned short inputAndValidation(unsigned short* pI);
    void waveletTransform2D(unsigned char* arr, unsigned int rowLen, unsigned int colLen, unsigned short level);
    void rearrange2DFromLR(unsigned char* arr, unsigned int rowLen, unsigned int colLen, unsigned int decimatingColLen, unsigned int decimatingRowIndex);// decimatingRowIndex is zero-based row index
    void revertRearrange2DFromLR(unsigned char* arr, unsigned int rowLen, unsigned int colLen, unsigned int runningColLen, unsigned int runningRowIndex);// runningRowIndex is zero-based row index
    void rearrange2DFromTC(unsigned char* arr, unsigned int rowLen, unsigned int colLen, unsigned int decimatingRowLen, unsigned int decimatingColumnIndex);// decimatingColumnIndex is zero-based column index
    void revertRearrange2DFromTC(unsigned char* arr, unsigned int rowLen, unsigned int colLen, unsigned int runningRowLen, unsigned int runningColumnIndex); // runningColumnIndex is zero-based column index
    void invWaveletTransform2D(unsigned char* arr, unsigned int rowLen, unsigned int colLen, unsigned short level);
    unsigned int twoExpLevel(unsigned short iLevel);
    void crtFlatArr(unsigned char* const pUch, const cv::Mat myImage);
    void crtMatArr(unsigned char* const pUch, cv::Mat& myImage);
    void printArr2D(unsigned char* arr, unsigned int rowLen, unsigned int colLen);
};

#endif