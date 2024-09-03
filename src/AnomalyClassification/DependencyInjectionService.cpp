#include "DependencyInjectionService.h"

DependencyInjectionService::DependencyInjectionService()
{
    this->stringSerivce = new StringSerivce();
    this->colorService = new ColorService();
    this->mathSerivce = new MathSerivce();
    this->imgService = new CImgService(this->colorService);
    this->superPixelService = new SuperPixelService(this->colorService, this->mathSerivce);
    this->classicSobelOperatorService = new ClassicSobelOperatorService(this->colorService);
    this->improvedSobelOperatorService = new ImprovedSobelOperatorService(this->colorService);
    this->geometricService = new GeometricService(this->colorService);
    this->histogramValueService = new HistogramValueService(this->colorService);
    this->discreteFourierTransformationSerivce = new DiscreteFourierTransformationSerivce(this->classicSobelOperatorService, this->colorService);
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
}