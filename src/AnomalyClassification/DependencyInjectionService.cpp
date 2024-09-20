#include "DependencyInjectionService.h"

DependencyInjectionService::DependencyInjectionService()
{
    this->stringSerivce = new StringSerivce();
    this->colorService = new ColorService();
    this->mathSerivce = new MathSerivce();
    this->geometricService = new GeometricService(this->colorService);
    this->imgService = new CImgService(this->geometricService, this->colorService);
    this->fileService = new FileService();

    this->defectGenerationService = new DefectGenerationService();

    this->superPixelService = new SuperPixelService(this->colorService, this->mathSerivce);
    this->classicSobelOperatorService = new ClassicSobelOperatorService(this->colorService);
    this->improvedSobelOperatorService = new ImprovedSobelOperatorService(this->colorService);
    this->histogramValueService = new HistogramValueService(this->colorService);
    this->discreteFourierTransformationSerivce = new DiscreteFourierTransformationSerivce(this->classicSobelOperatorService, this->imgService, this->colorService);
    this->directoryService = new DirectoryService(this->stringSerivce);
    this->huMomentsService = new HuMomentsService(this->colorService);
    this->sdSfService = new SdSfService(this->classicSobelOperatorService, this->geometricService, this->mathSerivce, this->stringSerivce, this->colorService);
    this->lbpService = new LbpService(this->geometricService, this->mathSerivce, this->colorService);
    this->completedLbpService = new CompletedLbpService(this->geometricService, this->mathSerivce, this->colorService);
    this->glcmService = new GLCMService(this->imgService);
    this->gaborServiceCV = new GaborServiceCV();
    this->hogService = new HOGService(this->classicSobelOperatorService, this->imgService, this->mathSerivce);
    this->waveletTransformCV = new WaveletTransformCV(this->stringSerivce);
    this->discreteFourierTransformationSerivceCV = new DiscreteFourierTransformationSerivceCV();
    this->discreteFourierDescriptorService = new DiscreteFourierDescriptorService(this->classicSobelOperatorService, this->imgService);
    this->daubechiesFourWaveletService = new DaubechiesFourWaveletService();
    this->morletWaveletService = new MorletWaveletService(this->mathSerivce);
    this->morletWaveletServiceFFT = new MorletWaveletServiceFFT();
    this->haarWavletService = new HaarWavletService();
    this->daubechiesSecondWaveletService = new DaubechiesSecondWaveletService();
    this->biorWavletService = new BiorWavletService();

    this->kNearestNeighborsService = new KNearestNeighborsService();
}

DependencyInjectionService::~DependencyInjectionService()
{
    delete this->stringSerivce;
    delete this->colorService;
    delete this->mathSerivce;
    delete this->imgService;
    delete this->superPixelService;
    delete this->classicSobelOperatorService;
    delete this->improvedSobelOperatorService;
    delete this->geometricService;
    delete this->fileService;

    delete this->defectGenerationService;

    delete this->histogramValueService;
    delete this->discreteFourierTransformationSerivce;
    delete this->directoryService;
    delete this->huMomentsService;
    delete this->sdSfService;
    delete this->lbpService;
    delete this->completedLbpService;
    delete this->glcmService;
    delete this->gaborServiceCV;
    delete this->hogService;
    delete this->waveletTransformCV;
    delete this->discreteFourierTransformationSerivceCV;
    delete this->discreteFourierDescriptorService;
    delete this->daubechiesFourWaveletService;
    delete this->morletWaveletService;
    delete this->morletWaveletServiceFFT;
    delete this->haarWavletService;
    delete this->daubechiesSecondWaveletService;
    delete this->biorWavletService;

    delete this->kNearestNeighborsService;
}