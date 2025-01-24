#ifndef DependencyInjectionService_H
#define DependencyInjectionService_H

#include "GraphicEngineExtended.h"
#include "SuperPixelService.h"
#include "ColorService.h"
#include "StringSerivce.h"
#include "CImgService.h"
#include "ClassicSobelOperatorService.h"
#include "ImprovedSobelOperatorService.h"
#include "GeometricService.h"
#include "HistogramValueService.h"
#include "DiscreteFourierTransformationSerivce.h"
#include "DirectoryService.h"
#include "HuMomentsService.h"
#include "LbpService.h"
#include "CompletedLbpService.h"
#include "GLCMService.h"
#include "HOGService.h"
#include "GaborServiceCV.h"
#include "WaveletTransformCV.h"
#include "SdSfService.h"
#include "DiscreteFourierTransformationSerivceCV.h"
#include "DiscreteFourierDescriptorService.h"
#include "DaubechiesFourWaveletService.h"
#include "MorletWaveletService.h"
#include "MorletWaveletServiceFFT.h"
#include "HaarWavletService.h"
#include "DaubechiesSecondWaveletService.h"
#include "BiorWavletService.h"
#include "FileService.h"
#include "PythonExecuter.h"
#include "TempFileNameService.h"
#include "ImageFixService.h"

#include "KNearestNeighborsService.h"
#include "DecisionTreeService.h"
#include "SvmService.h"
#include "KMeansService.h"

#include "../AnomalyGeneration/DefectGenerationService.h"

class DependencyInjectionService
{
public:
    StringSerivce* stringSerivce;
    ColorService* colorService;
    MathSerivce* mathSerivce;
    CImgService* imgService;
    SuperPixelService* superPixelService;
    FileService* fileService;
    TempFileNameService* tempFileNameService;

    DefectGenerationService* defectGenerationService;

    ClassicSobelOperatorService* classicSobelOperatorService;
    ImprovedSobelOperatorService* improvedSobelOperatorService;
    GeometricService* geometricService;
    HistogramValueService* histogramValueService;
    DirectoryService* directoryService;
    HuMomentsService* huMomentsService;
    SdSfService* sdSfService;
    LbpService* lbpService;
    CompletedLbpService* completedLbpService;
    GLCMService* glcmService;
    GaborServiceCV* gaborServiceCV;
    HOGService* hogService;
    WaveletTransformCV* waveletTransformCV;
    DiscreteFourierTransformationSerivceCV* discreteFourierTransformationSerivceCV;
    DiscreteFourierDescriptorService* discreteFourierDescriptorService;
    MorletWaveletService* morletWaveletService;

#ifdef _USE_PYTHON_SCRIPTS
    FastFourierDescriptorService* discreteFourierTransformationSerivce;
    MorletWaveletPythonService* morletWaveletServiceFFT;
    HaarWaveletPythonService* haarWavletService;
    Db2WaveletPythonService* daubechiesSecondWaveletService;
    Db4WaveletPythonService* daubechiesFourWaveletService;
#else
    DiscreteFourierTransformationSerivce* discreteFourierTransformationSerivce;
    MorletWaveletServiceFFT* morletWaveletServiceFFT;
    HaarWavletService* haarWavletService;
    DaubechiesSecondWaveletService* daubechiesSecondWaveletService;
    DaubechiesFourWaveletService* daubechiesFourWaveletService;
#endif
    BiorWavletService* biorWavletService;
    Yolov10Service* yolov10Service;

    KNearestNeighborsService* kNearestNeighborsService;
    DecisionTreeService* decisionTreeService;
    SvmService* svmService;
    KMeansService* kmeansService;

    ImageFixService* imageFixService;

public:
    DependencyInjectionService();
    ~DependencyInjectionService();

};

#endif