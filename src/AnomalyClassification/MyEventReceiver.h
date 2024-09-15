#ifndef MyEventReceiver_H
#define MyEventReceiver_H

#include <activation.h>
#include <iostream>
#include <cstdio>
#include <sstream> 
#include <thread>
#include <future>

#include "memblock.h"
#include "chartdir.h"
#include <irrlicht.h>
#include "driverChoice.h"

#include "GraphicEngineExtended.h"
#include "../IrrlichtWrapper/SAppContext.h"
#include "../IrrlichtWrapper/EventReceiver.h"
/*
#include "SuperPixelService.h"
#include "ClassicSobelOperatorService.h"
#include "ImprovedSobelOperatorService.h"
#include "GeometricService.h"
#include "HistogramValueService.h"
#include "DiscreteFourierTransformationSerivce.h"
#include "HuMomentsService.h"
#include "DirectoryService.h"
#include "SdSfService.h"
#include "LbpService.h"
#include "CompletedLbpService.h"
#include "GLCMService.h"
#include "HOGService.h"
#include "GaborServiceCV.h"*/

#include "DependencyInjectionService.h"

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/gapi/imgproc.hpp>
#include <opencv2/gapi/gkernel.hpp>
#include <opencv2/gapi/gmat.hpp>
#include <opencv2/gapi/gscalar.hpp>
#include <opencv2/imgproc.hpp>

#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
#include <iomanip>

#define stringify( name ) #name

enum {
    GUI_ID_OPERATION_PANNEL,
    GUI_ID_GRAYINFO_PANNEL,
    GUI_ID_GEOMETRICINFO_PANNEL,
    GUI_ID_IMAGE_PANNEL,
    GUI_ID_HU_MOMENT_PANNEL,
    GUI_ID_HU_GLCM_PANNEL,

    GUI_ID_TABCONTROL,
    GUI_ID_IMAGE_1_TAB,
    GUI_ID_IMAGE_2_TAB,
    GUI_ID_IMAGE_3_TAB,

    GUI_ID_IMAGE_1,
    GUI_ID_IMAGE_2_0,
    GUI_ID_IMAGE_2_1,
    GUI_ID_IMAGE_3_0,
    GUI_ID_IMAGE_3_1,

    GUI_ID_CHECKBOX_SUPERPIXELS,
    GUI_ID_CHECKBOX_SOBEL,
    GUI_ID_CHECKBOX_IMPROVED_SOBEL,
    GUI_ID_CHECKBOX_DISCRETE_FOURIER_TRANSFORMATION,
    GUI_ID_CHECKBOX_HU_MOMENT,
    GUI_ID_CHECKBOX_UNKNOWN,
    GUI_ID_CHECKBOX_SDSF,
    GUI_ID_CHECKBOX_LBP,
    GUI_ID_CHECKBOX_COMPLETED_LBP,
    GUI_ID_CHECKBOX_GLCM,
    GUI_ID_CHECKBOX_HOG,
    GUI_ID_CHECKBOX_GABOR,
    GUI_ID_CHECKBOX_WAVELET,
    GUI_ID_CHECKBOX_DISCRETE_FOURIER_TRANSFORMATION_CV,
    GUI_ID_CHECKBOX_FOURIER_DISCRIPTOR,
    GUI_ID_CHECKBOX_DAUBECHIES_FOUR_WAVELET,
    GUI_ID_CHECKBOX_MORLET_WAVELET,
    GUI_ID_CHECKBOX_MORLET_WAVELET_FFT,
    GUI_ID_CHECKBOX_HAAR_WAVLET,
    GUI_ID_CHECKBOX_DAUBECHIES_SECOND,
    GUI_ID_CHECKBOX_BIOR_WAVLET,

    GUI_ID_BUTTON_CACLULATE,
    GUI_ID_BUTTON_CHOOSE_FILE,
    GUI_ID_DIALOG_CHOOSE_FILE,
    GUI_ID_LABEL_DEFECT_COLOR,
    GUI_ID_LABEL_BACKGROUND_COLOR,
    GUI_ID_LABEL_ROI,
    GUI_ID_LABEL_AREA,
    GUI_ID_LABEL_RATIO_AREA_ROI,
    GUI_ID_LABEL_RATIO_WIDTH_LENGTH,
    GUI_ID_LABEL_SCOPE,
    GUI_ID_LABEL_DEFECT_FOCUS,
    GUI_ID_LABEL_MEAN,
    GUI_ID_LABEL_VARIANCE,
    GUI_ID_LABEL_SKEWNESS,
    GUI_ID_LABEL_KURTOSIS,
    GUI_ID_LABEL_POWER,
    GUI_ID_LABEL_ENTROPY,
    GUI_ID_LABEL_RECTANGULARITY,
    GUI_ID_VALUE_DEFECT_COLOR,
    GUI_ID_VALUE_BACKGROUND_COLOR,
    GUI_ID_VALUE_ROI,
    GUI_ID_VALUE_AREA,
    GUI_ID_VALUE_RATIO_AREA_ROI,
    GUI_ID_VALUE_RATIO_WIDTH_LENGTH,
    GUI_ID_VALUE_SCOPE,
    GUI_ID_VALUE_DEFECT_FOCUS,
    GUI_ID_VALUE_MEAN,
    GUI_ID_VALUE_VARIANCE,
    GUI_ID_VALUE_SKEWNESS,
    GUI_ID_VALUE_KURTOSIS,
    GUI_ID_VALUE_POWER,
    GUI_ID_VALUE_ENTROPY,
    GUI_ID_VALUE_RECTANGULARITY,
    GUI_ID_LABEL_HU_OWN,
    GUI_ID_LABEL_HU_OWN_1,
    GUI_ID_LABEL_HU_OWN_2,
    GUI_ID_LABEL_HU_OWN_3,
    GUI_ID_LABEL_HU_OWN_4,
    GUI_ID_LABEL_HU_OWN_5,
    GUI_ID_LABEL_HU_OWN_6,
    GUI_ID_LABEL_HU_OWN_7,
    GUI_ID_VALUE_HU_OWN_1,
    GUI_ID_VALUE_HU_OWN_2,
    GUI_ID_VALUE_HU_OWN_3,
    GUI_ID_VALUE_HU_OWN_4,
    GUI_ID_VALUE_HU_OWN_5,
    GUI_ID_VALUE_HU_OWN_6,
    GUI_ID_VALUE_HU_OWN_7,
    GUI_ID_LABEL_HU_OPENCV,
    GUI_ID_LABEL_HU_OPENCV_1,
    GUI_ID_LABEL_HU_OPENCV_2,
    GUI_ID_LABEL_HU_OPENCV_3,
    GUI_ID_LABEL_HU_OPENCV_4,
    GUI_ID_LABEL_HU_OPENCV_5,
    GUI_ID_LABEL_HU_OPENCV_6,
    GUI_ID_LABEL_HU_OPENCV_7,
    GUI_ID_VALUE_HU_OPENCV_1,
    GUI_ID_VALUE_HU_OPENCV_2,
    GUI_ID_VALUE_HU_OPENCV_3,
    GUI_ID_VALUE_HU_OPENCV_4,
    GUI_ID_VALUE_HU_OPENCV_5,
    GUI_ID_VALUE_HU_OPENCV_6,
    GUI_ID_VALUE_HU_OPENCV_7,

    GUI_ID_LABEL_GLCM_ENERGY,
    GUI_ID_LABEL_GLCM_CONTRAST,
    GUI_ID_LABEL_GLCM_HOMOGENITY,
    GUI_ID_LABEL_GLCM_IDM,
    GUI_ID_LABEL_GLCM_ENTROPY,
    GUI_ID_LABEL_GLCM_MEAN,
    GUI_ID_VALUE_GLCM_ENERGY,
    GUI_ID_VALUE_GLCM_CONTRAST,
    GUI_ID_VALUE_GLCM_HOMOGENITY,
    GUI_ID_VALUE_GLCM_IDM,
    GUI_ID_VALUE_GLCM_ENTROPY,
    GUI_ID_VALUE_GLCM_MEAN,
};

class MyEventReceiver : public EventReceiver
{
private:
    GraphicEngineExtended* graphicEngine;
    SAppContext* context;
    StringSerivce* stringSerivce;
    DirectoryService* directoryService;
    MathSerivce* mathSerivce;
    ColorService* colorService;
    CImgService* cImgService;

    SuperPixelService* superPixelService;
    ClassicSobelOperatorService* sobelOperatorSerivce;
    ImprovedSobelOperatorService* improvedSobelOperatorService;
    GeometricService* geometricService;
    HistogramValueService* histogramValueService;
    DiscreteFourierTransformationSerivce* discreteFourierTransformationSerivce;
    HuMomentsService* huMomentsService;
    SdSfService* sdSfService;
    LbpService* lbpService;
    CompletedLbpService* completedLbpService;
    GLCMService* glcmService;
    HOGService* hogService;
    GaborServiceCV* gaborServiceCV;
    WaveletTransformCV* waveletTransformCV;
    DiscreteFourierTransformationSerivceCV* discreteFourierTransformationSerivceCV;
    DiscreteFourierDescriptorService* discreteFourierDescriptorService;
    DaubechiesFourWaveletService* daubechiesFourWaveletService;
    MorletWaveletService* morletWaveletService;
    MorletWaveletServiceFFT* morletWaveletServiceFFT;
    HaarWavletService* haarWaeletService;
    DaubechiesSecondWaveletService* daubechiesSecondWaveletService;
    BiorWavletService* biorWavlet;

    std::thread currentAlgorithmThread;
    std::thread currentSimulationThread;

    bool isRunning;
    bool isAbbord;

    wchar_t progressSymbol;

    double coverageOfLastRun;
    int imageCountOfLastRun;

    std::wstring selectedFile;
    int tempFileIndex;

    bool imageVectorCentered = true; 
    bool imageVectorByConture = true;

public:
    MyEventReceiver(GraphicEngineExtended* graphic_engine, DependencyInjectionService* dependencyInjectionService);
    ~MyEventReceiver();

    virtual void OnInit(SAppContext* context);

    bool setForm(s32 id);
    virtual bool OnEvent(const SEvent& event);

private:
    void onCalculateSuperPixels();
    void onCalculateSobelOperator();
    void onCalculateImprovedSobelOperator();
    void onDiscreteFourierTransformation();
    void onHuMoment();
    void onSdSf();
    void onLbp();
    void onCompletedLbp();
    void onGLCM();
    void onHOG();
    void onGaborFilter();
    void onWavelet();
    void onDiscreteFourierTransformationCV();
    void onFourierDiscriptor();
    void onDaubechiesFourWavelet();
    void onMorletFourWavelet();
    void onMorletFourWaveletFFT();
    void onHaarWavelet();
    void onDaubechiesSecond();
    void onBiorWavlet();

    void onSelectFile(core::stringc fileName);
    void onResetImages();
    void onCreateImagePannel();

    void superPixelToImage(std::vector<std::vector<SuperPixelEntry>> pixelCluster, int width, int height, std::string tempPath);
    std::string generateFileName();
    void removeTempFiles();

    void histogram(std::map<int, int> histogramData, int labelCount, std::string fileName);
    void histogram(std::map<std::string, int> histogramData, int labelCount, std::string fileName);
    void diagram(std::vector<std::complex<double>> data, std::string fileName, std::vector<double> discription = std::vector<double>(0), std::string title = "");
    void diagram(std::vector<double> data, std::string fileName);
    void diagram(std::vector<std::complex<double>> data, std::string fileName, std::vector<std::complex<double>> complexDiscription, std::string title = "");
    void heatMap(TimeFrequenceResult timeFrequence, std::vector<double> labels, std::string fileName);
    void heatMap(std::map<int, std::vector<std::complex<double>>> input, int maxLevel, std::vector<double> labels, std::string fileName);
    void heatMapImg(TimeFrequenceResult timeFrequence, std::string fileName);

    double* generateNewArray(int to);
    double* generateNewArrayFromExsistingFrequence(std::map<int, std::vector<std::complex<double>>> frequenceTimeMap, int maxFrequence);
    double* generateNewArrayFromExsistingFrequence(TimeFrequenceResult timeFrequence);

    std::map<double, std::vector<double>> toDoubleMap(std::map<double, std::vector<std::complex<double>>> a);
};

#endif