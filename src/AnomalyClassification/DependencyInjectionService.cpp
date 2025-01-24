#include "DependencyInjectionService.h"

DependencyInjectionService::DependencyInjectionService()
{
    this->stringSerivce = new StringSerivce();
    this->colorService = new ColorService();
    this->mathSerivce = new MathSerivce();
    this->geometricService = new GeometricService(this->colorService);
    this->imgService = new CImgService(this->geometricService, this->colorService);
    this->fileService = new FileService();
    this->tempFileNameService = new TempFileNameService(this->directoryService, this->stringSerivce);

    this->defectGenerationService = new DefectGenerationService();

    this->superPixelService = new SuperPixelService(this->colorService, this->mathSerivce);
    this->classicSobelOperatorService = new ClassicSobelOperatorService(this->colorService);
    this->improvedSobelOperatorService = new ImprovedSobelOperatorService(this->colorService);
    this->histogramValueService = new HistogramValueService(this->colorService);
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
    this->morletWaveletService = new MorletWaveletService(this->mathSerivce);
#ifdef _USE_PYTHON_SCRIPTS
    this->discreteFourierTransformationSerivce = new FastFourierDescriptorService(this->stringSerivce, this->tempFileNameService, this->fileService);
    this->morletWaveletServiceFFT = new MorletWaveletPythonService(this->stringSerivce, this->tempFileNameService, this->fileService);
    this->haarWavletService = new HaarWaveletPythonService(this->stringSerivce, this->tempFileNameService, this->fileService);
    this->daubechiesSecondWaveletService = new Db2WaveletPythonService(this->stringSerivce, this->tempFileNameService, this->fileService);
    this->daubechiesFourWaveletService = new Db4WaveletPythonService(this->stringSerivce, this->tempFileNameService, this->fileService);
#else
    this->discreteFourierTransformationSerivce = new DiscreteFourierTransformationSerivce(this->classicSobelOperatorService, this->imgService, this->colorService);
    this->morletWaveletServiceFFT = new MorletWaveletServiceFFT();
    this->haarWavletService = new HaarWavletService(); 
    this->daubechiesSecondWaveletService = new DaubechiesSecondWaveletService();
    this->daubechiesFourWaveletService = new DaubechiesFourWaveletService();
#endif
    this->biorWavletService = new BiorWavletService();
    this->yolov10Service = new Yolov10Service(this->stringSerivce, this->tempFileNameService, this->fileService);

    this->kNearestNeighborsService = new KNearestNeighborsService();
    this->decisionTreeService = new DecisionTreeService(this->stringSerivce, this->tempFileNameService, this->fileService);
    this->svmService = new SvmService(this->stringSerivce, this->tempFileNameService, this->fileService);
    this->kmeansService = new KMeansService(this->stringSerivce, this->tempFileNameService, this->fileService);

    this->imageFixService = new ImageFixService(this->geometricService, this->colorService, this->tempFileNameService);
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
    delete this->tempFileNameService;

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
    delete this->yolov10Service;

    delete this->kNearestNeighborsService;
    delete this->decisionTreeService;
    delete this->svmService;
    delete this->kmeansService;

    delete this->imageFixService;
}