#include "MyEventReceiver.h"

MyEventReceiver::MyEventReceiver(GraphicEngineExtended* graphicEngine, DependencyInjectionService* di)
{
    this->graphicEngine = graphicEngine;
    this->superPixelService = di->superPixelService;
    this->sobelOperatorSerivce = di->classicSobelOperatorService;
    this->improvedSobelOperatorService = di->improvedSobelOperatorService;
    this->geometricService = di->geometricService;
    this->histogramValueService = di->histogramValueService;
    this->discreteFourierTransformationSerivce = di->discreteFourierTransformationSerivce;
    this->huMomentsService = di->huMomentsService;
    this->sdSfService = di->sdSfService;
    this->lbpService = di->lbpService;
    this->completedLbpService = di->completedLbpService;
    this->glcmService = di->glcmService;
    this->hogService = di->hogService;
    this->gaborServiceCV = di->gaborServiceCV;
    this->waveletTransformCV = di->waveletTransformCV;
    this->discreteFourierTransformationSerivceCV = di->discreteFourierTransformationSerivceCV;
    this->discreteFourierDescriptorService = di->discreteFourierDescriptorService;

    this->stringSerivce = di->stringSerivce;
    this->directoryService = di->directoryService;

    this->facet = NULL;
    this->context = NULL;

    this->isRunning = false;
    this->isAbbord = false;

    this->progressSymbol = '-';
    this->selectedFile = L"";
    this->tempFileIndex = 0;
}

MyEventReceiver::~MyEventReceiver()
{
    this->isAbbord = true;

    if (this->isRunning)
    {
        //this->onJoinTask();
    }

    this->removeTempFiles();
}

void MyEventReceiver::OnInit(SAppContext* context)
{
    this->context = context;
}

bool MyEventReceiver::setForm(s32 id)
{
    switch (id) {
    case 1:
        break;
    default:
        return false;
    }
}

bool MyEventReceiver::OnEvent(const SEvent& event)
{
    if (event.EventType == EET_GUI_EVENT)
    {
        s32 id = event.GUIEvent.Caller->getID();

        IGUIEnvironment* env = this->context->device->getGUIEnvironment();

        switch (event.GUIEvent.EventType)
        {
        case EGET_SCROLL_BAR_CHANGED:

            break;
        case EGET_BUTTON_CLICKED:

            if (id == GUI_ID_BUTTON_CACLULATE)
            {
                if (this->graphicEngine->isCheckboxChecked(GUI_ID_CHECKBOX_SUPERPIXELS))
                {
                    this->onCalculateSuperPixels();
                }
                else if (this->graphicEngine->isCheckboxChecked(GUI_ID_CHECKBOX_SOBEL))
                {
                    this->onCalculateSobelOperator();
                }
                else if (this->graphicEngine->isCheckboxChecked(GUI_ID_CHECKBOX_IMPROVED_SOBEL))
                {
                    this->onCalculateImprovedSobelOperator();
                }
                else if(this->graphicEngine->isCheckboxChecked(GUI_ID_CHECKBOX_DISCRETE_FOURIER_TRANSFORMATION))
                {
                    this->onDiscreteFourierTransformation();
                }
                else if(this->graphicEngine->isCheckboxChecked(GUI_ID_CHECKBOX_HU_MOMENT))
                {
                    this->onHuMoment();
                }
                else if (this->graphicEngine->isCheckboxChecked(GUI_ID_CHECKBOX_SDSF))
                {
                    this->onSdSf();
                }
                else if (this->graphicEngine->isCheckboxChecked(GUI_ID_CHECKBOX_LBP))
                {
                    this->onLbp();
                }
                else if (this->graphicEngine->isCheckboxChecked(GUI_ID_CHECKBOX_COMPLETED_LBP))
                {
                    this->onCompletedLbp();
                }
                else if (this->graphicEngine->isCheckboxChecked(GUI_ID_CHECKBOX_GLCM))
                {
                    this->onGLCM();
                }
                else if (this->graphicEngine->isCheckboxChecked(GUI_ID_CHECKBOX_HOG))
                {
                    this->onHOG();
                }
                else if (this->graphicEngine->isCheckboxChecked(GUI_ID_CHECKBOX_GABOR))
                {
                    this->onGaborFilter();
                }
                else if (this->graphicEngine->isCheckboxChecked(GUI_ID_CHECKBOX_WAVELET))
                {
                    this->onWavelet();
                }
                else if (this->graphicEngine->isCheckboxChecked(GUI_ID_CHECKBOX_DISCRETE_FOURIER_TRANSFORMATION_CV))
                {
                    this->onDiscreteFourierTransformationCV();
                }
                else if (this->graphicEngine->isCheckboxChecked(GUI_ID_CHECKBOX_FOURIER_DISCRIPTOR))
                {
                    this->onFourierDiscriptor();
                }
            }
            else if (id == GUI_ID_BUTTON_CHOOSE_FILE)
            {
                this->onResetImages();
                this->graphicEngine->addFileOpenDialog(GUI_ID_DIALOG_CHOOSE_FILE, L"..\\AnomalyGeneration\\testdata");
            }

             return true;
        case EGET_FILE_SELECTED:
        {
            IGUIFileOpenDialog* dialog =
                (IGUIFileOpenDialog*)event.GUIEvent.Caller;

            this->onSelectFile(core::stringc(dialog->getFileName()).c_str());
            return true;
        }
        case EGET_CHECKBOX_CHANGED:
            this->graphicEngine->resetMethodCheckBoxs();
            this->graphicEngine->setGUIElementChecked(id, true);

            return true;

        default:
            return this->setForm(id);
        }
    }

    return false;
}
/*
void display_superimposed(const cv::Mat& A1, const cv::Mat& B, const std::string& fileName)
{
    cv::Mat A;
    cv::Mat C;

    cvtColor(A1, A, cv::COLOR_BGR2GRAY);

    int aChannels = A.channels();
    int bChannels = B.channels();

    if(aChannels != bChannels)
    {
        throw "Ungleiche Channels";
    }

    try
    {
        cv::addWeighted(A, 0.5, B, 0.5, 0.0, C, C.type());
    }
    catch(cv::Exception e)
    {
        std::cout << e.what();
    }
    
    cv::imwrite(fileName, C);
}

cv::Mat custom_normalization(const cv::Mat& src) {
    double min, max;
    cv::minMaxLoc(src, &min, &max);
    cv::Mat dst = src * 200 / (max - min) + 128;
    dst.convertTo(dst, CV_8U);
    return dst;
}*/

void MyEventReceiver::onFourierDiscriptor()
{
    std::string fileName = this->stringSerivce->toString(this->selectedFile);
    CImg<unsigned char> img(fileName.c_str());

    FDResult result = this->discreteFourierDescriptorService->calculate(&img);

    // Add Sobelimage
    std::string tempName = this->generateFileName();
    result.sobelImage.save_png(tempName.c_str());
    this->graphicEngine->addImage(GUI_ID_IMAGE_2, Point2D(8, 10), this->stringSerivce->toWString(tempName).c_str(), GUI_ID_IMAGE_2_TAB);


    // Add Diagram
    tempName = this->generateFileName();
    this->diagram(result.fequence, tempName);
    this->graphicEngine->addImage(GUI_ID_IMAGE_3, Point2D(8, 10), this->stringSerivce->toWString(tempName).c_str(), GUI_ID_IMAGE_3_TAB);
    
    // Clean up
    this->removeTempFiles();
}

void MyEventReceiver::onDiscreteFourierTransformationCV()
{
    std::string fileName = this->stringSerivce->toString(this->selectedFile);
    DFTResult result = this->discreteFourierTransformationSerivceCV->calculate(fileName);

    std::string tempName = this->generateFileName();
    cv::imwrite(tempName.c_str(), result.spectrumMagnitude*255);
    this->graphicEngine->addImage(GUI_ID_IMAGE_2, Point2D(8, 10), this->stringSerivce->toWString(tempName).c_str(), GUI_ID_IMAGE_2_TAB);

    tempName = this->generateFileName();
    this->diagram(result.radialProfile, tempName);
    this->graphicEngine->addImage(GUI_ID_IMAGE_3, Point2D(8, 10), this->stringSerivce->toWString(tempName).c_str(), GUI_ID_IMAGE_3_TAB);

    // Clean up
    this->removeTempFiles();
}

void MyEventReceiver::onWavelet()
{
    // Wavelet
    std::string fileName = this->stringSerivce->toString(this->selectedFile);
    this->waveletTransformCV->calculate(fileName);

    // Clean up
    this->removeTempFiles();
}

void MyEventReceiver::onGaborFilter()
{
    // Gabor
    std::string fileName = this->stringSerivce->toString(this->selectedFile);
    std::vector<double> fequence = this->gaborServiceCV->calculate(fileName);

    std::string tempName = this->generateFileName();
    this->diagram(fequence, tempName);
    this->graphicEngine->addImage(GUI_ID_IMAGE_2, Point2D(8, 10), this->stringSerivce->toWString(tempName).c_str(), GUI_ID_IMAGE_2_TAB);

    // Clean up
    this->removeTempFiles();
}

void MyEventReceiver::onHOG()
{
    std::string fileName = this->stringSerivce->toString(this->selectedFile);
    CImg<unsigned char> img(fileName.c_str());

    ColorRGB backgroundColor = this->geometricService->getBackgroundColor(&img);

    // HOG
    /*cv::Mat image = cv::imread(fileName);
    this->hogService->process(image);

    auto hist = this->hogService->retrieve(cv::Rect(0, 0, image.cols, image.rows));

    //display_superimposed(image, this->hogService->get_vector_mask(2), "vector_mask");

    // magnitude
    fileName = this->generateFileName();
    display_superimposed(custom_normalization(this->hogService->get_magnitudes()), this->hogService->get_vector_mask(2), fileName);
    this->graphicEngine->addImage(GUI_ID_IMAGE_2, Point2D(8, 10), this->stringSerivce->toWString(fileName).c_str(), GUI_ID_IMAGE_2_TAB);

    // orientation
    fileName = this->generateFileName();
    display_superimposed(custom_normalization(this->hogService->get_orientations()), this->hogService->get_vector_mask(2), fileName);
    this->graphicEngine->addImage(GUI_ID_IMAGE_3, Point2D(8, 10), this->stringSerivce->toWString(fileName).c_str(), GUI_ID_IMAGE_3_TAB);*/

    std::vector<double> theVector = this->hogService->calculate(&img);

    // Clean up
    this->removeTempFiles();
}

void MyEventReceiver::onGLCM()
{
    std::string fileName = this->stringSerivce->toString(this->selectedFile);
    CImg<unsigned char> img(fileName.c_str());

    ColorRGB backgroundColor = this->geometricService->getBackgroundColor(&img);

    // GLCM
    GLCMResult result = this->glcmService->calculate(&img);

    // Generate FileName
    fileName = this->generateFileName();
    result.getGlImage().save(fileName.c_str());
    this->graphicEngine->addImage(GUI_ID_IMAGE_2, Point2D(8, 10), this->stringSerivce->toWString(fileName).c_str(), GUI_ID_IMAGE_2_TAB);
    
    wstring valueString = this->stringSerivce->doubleToWString(result.getEnergy());
    this->graphicEngine->setGUIElementText(GUI_ID_VALUE_GLCM_ENERGY, valueString.c_str());

    valueString = this->stringSerivce->doubleToWString(result.getContrast());
    this->graphicEngine->setGUIElementText(GUI_ID_VALUE_GLCM_CONTRAST, valueString.c_str());

    valueString = this->stringSerivce->doubleToWString(result.getHomogenity());
    this->graphicEngine->setGUIElementText(GUI_ID_VALUE_GLCM_HOMOGENITY, valueString.c_str());

    valueString = this->stringSerivce->doubleToWString(result.getIDM());
    this->graphicEngine->setGUIElementText(GUI_ID_VALUE_GLCM_IDM, valueString.c_str());

    valueString = this->stringSerivce->doubleToWString(result.getEntropy());
    this->graphicEngine->setGUIElementText(GUI_ID_VALUE_GLCM_ENTROPY, valueString.c_str());

    valueString = this->stringSerivce->doubleToWString(result.getMean());
    this->graphicEngine->setGUIElementText(GUI_ID_VALUE_GLCM_MEAN, valueString.c_str());

    // Clean up
    this->removeTempFiles();
}

void MyEventReceiver::onCompletedLbp()
{
    std::string fileName = this->stringSerivce->toString(this->selectedFile);
    CImg<unsigned char> img(fileName.c_str());

    ColorRGB backgroundColor = this->geometricService->getBackgroundColor(&img);

    // Sobel Image
    LbpHistogramResult result = this->completedLbpService->calculateLbpHistogram(&img, 8, 10);

    // Generate Diagram
    fileName = this->generateFileName();
    this->histogram(result.getLbpHistogram(), 5, fileName);
    this->graphicEngine->addImage(GUI_ID_IMAGE_2, Point2D(8, 10), this->stringSerivce->toWString(fileName).c_str(), GUI_ID_IMAGE_2_TAB);
    
    fileName = this->generateFileName();
    this->histogram(result.getUniformityHistogram(), 3, fileName);
    this->graphicEngine->addImage(GUI_ID_IMAGE_3, Point2D(8, 10), this->stringSerivce->toWString(fileName).c_str(), GUI_ID_IMAGE_3_TAB);
    
    // Clean up
    this->removeTempFiles();
}

void MyEventReceiver::onLbp()
{
    std::string fileName = this->stringSerivce->toString(this->selectedFile);
    CImg<unsigned char> img(fileName.c_str());

    ColorRGB backgroundColor = this->geometricService->getBackgroundColor(&img);

    // Sobel Image
    LbpHistogramResult result = this->lbpService->calculateLbpHistogram(&img, 8, 10);

    // Generate Diagram
    fileName = this->generateFileName();
    this->histogram(result.getLbpHistogram(), 5, fileName);
    this->graphicEngine->addImage(GUI_ID_IMAGE_2, Point2D(8, 10), this->stringSerivce->toWString(fileName).c_str(), GUI_ID_IMAGE_2_TAB);
    
    fileName = this->generateFileName();
    this->histogram(result.getUniformityHistogram(), 3, fileName);
    this->graphicEngine->addImage(GUI_ID_IMAGE_3, Point2D(8, 10), this->stringSerivce->toWString(fileName).c_str(), GUI_ID_IMAGE_3_TAB);
    
    // Clean up
    this->removeTempFiles();
}

void MyEventReceiver::onSdSf()
{
    std::string fileName = this->stringSerivce->toString(this->selectedFile);
    CImg<unsigned char> img(fileName.c_str());

    // Sobel Image
    CImg<unsigned char> sobelImage = this->improvedSobelOperatorService->getGradientImage(img);
    
    std::string sobelName = this->generateFileName();
    sobelImage.save(sobelName.c_str());
    this->graphicEngine->addImage(GUI_ID_IMAGE_2, Point2D(10, 10), this->stringSerivce->toWString(sobelName).c_str(), GUI_ID_IMAGE_2_TAB);

    // Create SD-SF-Diagram
    std::map<std::string, int> distanceHistogram = this->sdSfService->calculateSdSf(&sobelImage);

    fileName = this->generateFileName();
    this->histogram(distanceHistogram, 4, fileName);
    this->graphicEngine->addImage(GUI_ID_IMAGE_3, Point2D(10, 10), this->stringSerivce->toWString(fileName).c_str(), GUI_ID_IMAGE_3_TAB);

    // Clean up
    this->removeTempFiles();
}

void MyEventReceiver::onHuMoment()
{
    std::string fileName = this->stringSerivce->toString(this->selectedFile);
    CImg<unsigned char> img(fileName.c_str());

    try
    {
        double huMoments[7];
        int huMomentOpenCVMoments[] = { GUI_ID_VALUE_HU_OPENCV_1, GUI_ID_VALUE_HU_OPENCV_2, GUI_ID_VALUE_HU_OPENCV_3, GUI_ID_VALUE_HU_OPENCV_4, GUI_ID_VALUE_HU_OPENCV_5, GUI_ID_VALUE_HU_OPENCV_6, GUI_ID_VALUE_HU_OPENCV_7 };

        cv::Mat image = cv::imread(fileName.c_str(), cv::IMREAD_GRAYSCALE);
        cv::threshold(image, image, 128, 255, cv::THRESH_BINARY);

        // Calculate Moments 
        cv::Moments moments = cv::moments(image, false);
        // Calculate Hu Moments 
        cv::HuMoments(moments, huMoments);

        int length = sizeof(huMoments) / sizeof(double);
        for (int i = 0; i < length; i++)
        {
            std::wstring huString = this->stringSerivce->doubleToWString(huMoments[i]);
            this->graphicEngine->setGUIElementText(huMomentOpenCVMoments[i], huString.c_str());
        }
    }
    catch (cv::Exception e)
    {
        std::string message = e.what();
        int b = 0;
    }

    CImg<unsigned char> sobelImage = this->improvedSobelOperatorService->getGradientImage(img);

    // Output the chart
    std::string sobelName = this->generateFileName();
    sobelImage.save(sobelName.c_str());

    this->graphicEngine->addImage(GUI_ID_IMAGE_2, Point2D(10, 10), this->stringSerivce->toWString(sobelName).c_str(), GUI_ID_IMAGE_2_TAB);

    double hu = this->huMomentsService->calculateHu1(&sobelImage);
    std::wstring huString = this->stringSerivce->doubleToWString(hu);
    this->graphicEngine->setGUIElementText(GUI_ID_VALUE_HU_OWN_1, huString.c_str());

    hu = this->huMomentsService->calculateHu2(&sobelImage);
    huString = this->stringSerivce->doubleToWString(hu);
    this->graphicEngine->setGUIElementText(GUI_ID_VALUE_HU_OWN_2, huString.c_str());

    hu = this->huMomentsService->calculateHu3(&sobelImage);
    huString = this->stringSerivce->doubleToWString(hu);
    this->graphicEngine->setGUIElementText(GUI_ID_VALUE_HU_OWN_3, huString.c_str());

    hu = this->huMomentsService->calculateHu4(&sobelImage);
    huString = this->stringSerivce->doubleToWString(hu);
    this->graphicEngine->setGUIElementText(GUI_ID_VALUE_HU_OWN_4, huString.c_str());

    hu = this->huMomentsService->calculateHu5(&sobelImage);
    huString = this->stringSerivce->doubleToWString(hu);
    this->graphicEngine->setGUIElementText(GUI_ID_VALUE_HU_OWN_5, huString.c_str());

    hu = this->huMomentsService->calculateHu6(&sobelImage);
    huString = this->stringSerivce->doubleToWString(hu);
    this->graphicEngine->setGUIElementText(GUI_ID_VALUE_HU_OWN_6, huString.c_str());

    hu = this->huMomentsService->calculateHu7(&sobelImage);
    huString = this->stringSerivce->doubleToWString(hu);
    this->graphicEngine->setGUIElementText(GUI_ID_VALUE_HU_OWN_7, huString.c_str());

    this->removeTempFiles();
}

void MyEventReceiver::onDiscreteFourierTransformation()
{
    std::string cFile = this->stringSerivce->toString(this->selectedFile);
    CImg<unsigned char> img(cFile.c_str());

    // Output the chart
    FDResult result = this->discreteFourierTransformationSerivce->calculate(&img, 2000);
    
    // Add sobel image
    std::string fileName = this->generateFileName();
    result.sobelImage.save_png(fileName.c_str());
    this->graphicEngine->addImage(GUI_ID_IMAGE_2, Point2D(10, 10), this->stringSerivce->toWString(fileName).c_str(), GUI_ID_IMAGE_2_TAB);

    // Generate Diagram
    fileName = this->generateFileName();
    this->diagram(result.fequence, fileName);
    this->graphicEngine->addImage(GUI_ID_IMAGE_3, Point2D(10, 10), this->stringSerivce->toWString(fileName).c_str(), GUI_ID_IMAGE_3_TAB);

    // Clean Up
    this->removeTempFiles();
}

void MyEventReceiver::onCalculateSuperPixels()
{
    std::string cFile = this->stringSerivce->toString(this->selectedFile);

    CImg<unsigned char> img(cFile.c_str());
    SubregionResult result = this->superPixelService->calculateSuperPixelsAndSubregions(img, 50);

    std::string fileName = this->generateFileName();

    this->superPixelToImage(result.superPixelClusters, img.width(), img.height(), fileName);
    this->graphicEngine->addImage(GUI_ID_IMAGE_2, Point2D(10, 10), this->stringSerivce->toWString(fileName).c_str(), GUI_ID_IMAGE_2_TAB);

    fileName = this->generateFileName();

    this->superPixelToImage(result.subregions, img.width(), img.height(), fileName);
    this->graphicEngine->addImage(GUI_ID_IMAGE_3, Point2D(10, 10), this->stringSerivce->toWString(fileName).c_str(), GUI_ID_IMAGE_3_TAB);

    this->removeTempFiles();
}

void MyEventReceiver::onCalculateSobelOperator()
{
    std::string cFile = this->stringSerivce->toString(this->selectedFile);
    CImg<unsigned char> img(cFile.c_str());
    CImg<unsigned char> tempImage = this->sobelOperatorSerivce->getGradientImage(&img);

    std::string tempFileName = this->generateFileName();
    tempImage.save_png(tempFileName.c_str());
    
    this->graphicEngine->addImage(GUI_ID_IMAGE_3, Point2D(10, 10), this->stringSerivce->toWString(tempFileName).c_str(), GUI_ID_IMAGE_3_TAB);

    this->removeTempFiles();
}

void MyEventReceiver::onCalculateImprovedSobelOperator()
{
    std::string cFile = this->stringSerivce->toString(this->selectedFile);
    CImg<unsigned char> img(cFile.c_str());
    CImg<unsigned char> tempImage = this->improvedSobelOperatorService->getGradientImage(img);

    std::string tempFileName = this->generateFileName();
    tempImage.save_png(tempFileName.c_str());
    
    this->graphicEngine->addImage(GUI_ID_IMAGE_3, Point2D(10, 10), this->stringSerivce->toWString(tempFileName).c_str(), GUI_ID_IMAGE_3_TAB);

    this->removeTempFiles();
}

std::string MyEventReceiver::generateFileName()
{
    stringstream stream;
    std::string age_as_string;

    stream << this->tempFileIndex;
    stream >> age_as_string;

    std::string fileName = "temp";
    fileName += age_as_string;
    fileName += ".png";

    this->tempFileIndex++;

    return fileName;
}

void MyEventReceiver::removeTempFiles()
{
    std::vector<std::string> fileNames = this->directoryService->getFileNames(".");

    for(std::string fileName : fileNames)
    {
        if(this->stringSerivce->contains(fileName, "temp"))
        {
            std::remove(fileName.c_str());
        }
    }
}

void MyEventReceiver::onSelectFile(core::stringc fileName)
{
    this->onCreateImagePannel();
    
    CImg<unsigned char> img(fileName.c_str());
    
    std::wstring roiString = this->stringSerivce->intToWString(img.width()) + L" x " + this->stringSerivce->intToWString(img.height()) + L" px";
    this->graphicEngine->setGUIElementText(GUI_ID_VALUE_ROI, roiString.c_str());

    ColorRGB backgroundColor = this->geometricService->getBackgroundColor(&img);
    std::wstring backgroundColorString = this->stringSerivce->doubleToWString(backgroundColor.r)+L"|"+this->stringSerivce->doubleToWString(backgroundColor.g) + L"|" + this->stringSerivce->doubleToWString(backgroundColor.b);
    this->graphicEngine->setGUIElementText(GUI_ID_VALUE_BACKGROUND_COLOR, backgroundColorString.c_str());

    int defectPixels = this->geometricService->countDefectPixels(&img, backgroundColor);
    std::wstring defectPixelsString = this->stringSerivce->intToWString(defectPixels);
    std::wstring defectPixelsStringUnit = defectPixelsString + std::wstring(L" px");
    this->graphicEngine->setGUIElementText(GUI_ID_VALUE_AREA, defectPixelsStringUnit.c_str());

    double rotioRoiArea = defectPixels / ((double)img.width()) * ((double)img.height());
    std::wstring rotioRoiAreaString = this->stringSerivce->doubleToWString(rotioRoiArea);
    this->graphicEngine->setGUIElementText(GUI_ID_VALUE_RATIO_AREA_ROI, rotioRoiAreaString.c_str());

    double rotioWidthLength = ((double)img.width()) / ((double)img.height());
    std::wstring rotioWidthLengthString = this->stringSerivce->doubleToWString(rotioWidthLength);
    this->graphicEngine->setGUIElementText(GUI_ID_VALUE_RATIO_WIDTH_LENGTH, rotioWidthLengthString.c_str());

    int scope = this->geometricService->calculateScope(&img, backgroundColor);
    std::wstring scropWithUnit = this->stringSerivce->doubleToWString(scope) + L" px";
    this->graphicEngine->setGUIElementText(GUI_ID_VALUE_SCOPE, scropWithUnit.c_str());

    Point2D defectFocus = this->geometricService->calculateCentroid(&img, backgroundColor);
    std::wstring defectFocusString = L"(" + this->stringSerivce->doubleToWString(defectFocus.x) + L"px/" + this->stringSerivce->doubleToWString(defectFocus.y)+L"px)";
    this->graphicEngine->setGUIElementText(GUI_ID_VALUE_DEFECT_FOCUS, defectFocusString.c_str());

    double rectangularity = this->geometricService->calculateRectangularity(&img, backgroundColor);
    std::wstring rectangularityString = this->stringSerivce->doubleToWString(rectangularity);
    this->graphicEngine->setGUIElementText(GUI_ID_VALUE_RECTANGULARITY, rectangularityString.c_str());
    
    double mean = this->histogramValueService->getMean(&img);
    std::wstring meanString = this->stringSerivce->doubleToWString(mean);
    this->graphicEngine->setGUIElementText(GUI_ID_VALUE_MEAN, meanString.c_str());

    double variance = this->histogramValueService->getVariance(&img);
    std::wstring varianceString = this->stringSerivce->doubleToWString(variance);
    this->graphicEngine->setGUIElementText(GUI_ID_VALUE_VARIANCE, varianceString.c_str());

    double skewness = this->histogramValueService->getSkewness(&img);
    std::wstring skewnessString = this->stringSerivce->doubleToWString(skewness);
    this->graphicEngine->setGUIElementText(GUI_ID_VALUE_SKEWNESS, skewnessString.c_str());

    double kurtosis = this->histogramValueService->getKurtosis(&img);
    std::wstring kurtosisString = this->stringSerivce->doubleToWString(kurtosis);
    this->graphicEngine->setGUIElementText(GUI_ID_VALUE_KURTOSIS, kurtosisString.c_str());

    double power = this->histogramValueService->getPower(&img);
    std::wstring powerString = this->stringSerivce->doubleToWString(power);
    this->graphicEngine->setGUIElementText(GUI_ID_VALUE_POWER, powerString.c_str());

    double entropy = this->histogramValueService->getEntropy(&img);
    std::wstring entropyString = this->stringSerivce->doubleToWString(entropy);
    this->graphicEngine->setGUIElementText(GUI_ID_VALUE_ENTROPY, entropyString.c_str());
    
    std::wstring wFileName = this->stringSerivce->toWString(fileName.c_str());
    this->graphicEngine->addImage(GUI_ID_IMAGE_1, Point2D(10, 10), wFileName.c_str(), GUI_ID_IMAGE_1_TAB);

    this->selectedFile = wFileName.c_str();
}

void MyEventReceiver::superPixelToImage(std::vector<std::vector<SuperPixelEntry>> pixelCluster, int width, int height, std::string tempPath)
{
    const unsigned int size_z = 1;
    const unsigned int size_c = 3;

    CImg<unsigned int> bg(width, height, size_z, size_c, 255);

    for (int k = 0; k < pixelCluster.size(); k++)
    {
        const unsigned char(&color)[3] = { (unsigned char)(k * 75), (unsigned char)((k%3) * k * 75), (unsigned char)((k%5) * k * 75) };

        for (int i = 0; i < pixelCluster[k].size(); i++)
        {
            SuperPixelEntry entry = pixelCluster[k][i];
            bg.draw_point(entry.position.x, entry.position.y, color);
        }
    }

    bg.save_png(tempPath.c_str());
}

void MyEventReceiver::onCreateImagePannel()
{
    this->graphicEngine->addSubwindow(GUI_ID_IMAGE_PANNEL, Point2D(0, 0), Point2D(330, 480), L"Image");
    this->graphicEngine->addTabControl(GUI_ID_TABCONTROL, Point2D(0, 20), Point2D(330, 480), GUI_ID_IMAGE_PANNEL);
    this->graphicEngine->addTab(GUI_ID_IMAGE_1_TAB, L"Input image", GUI_ID_TABCONTROL);
    this->graphicEngine->addTab(GUI_ID_IMAGE_2_TAB, L"Process image", GUI_ID_TABCONTROL);
    this->graphicEngine->addTab(GUI_ID_IMAGE_3_TAB, L"Output image", GUI_ID_TABCONTROL);
}

void MyEventReceiver::onResetImages()
{
    if(this->graphicEngine->exists(GUI_ID_IMAGE_1))
    {
        this->graphicEngine->removeElement(GUI_ID_IMAGE_1);
    }

    if(this->graphicEngine->exists(GUI_ID_IMAGE_2))
    {
        this->graphicEngine->removeElement(GUI_ID_IMAGE_2);
    }

    if (this->graphicEngine->exists(GUI_ID_IMAGE_3))
    {
        this->graphicEngine->removeElement(GUI_ID_IMAGE_3);
    }

    if (this->graphicEngine->exists(GUI_ID_IMAGE_1_TAB))
    {
        this->graphicEngine->removeElement(GUI_ID_IMAGE_1_TAB);
    }

    if (this->graphicEngine->exists(GUI_ID_IMAGE_2_TAB))
    {
        this->graphicEngine->removeElement(GUI_ID_IMAGE_2_TAB);
    }

    if (this->graphicEngine->exists(GUI_ID_IMAGE_3_TAB))
    {
        this->graphicEngine->removeElement(GUI_ID_IMAGE_3_TAB);
    }

    if (this->graphicEngine->exists(GUI_ID_TABCONTROL))
    {
        this->graphicEngine->removeElement(GUI_ID_TABCONTROL);
    }

    if (this->graphicEngine->exists(GUI_ID_IMAGE_PANNEL))
    {
        this->graphicEngine->removeElement(GUI_ID_IMAGE_PANNEL);
    }
}

void MyEventReceiver::histogram(std::map<int, int> histogramData, int labelCount, std::string fileName)
{
    std::map<std::string, int> stringHistogramData;

    std::map<int, int>::iterator it;
    for (it = histogramData.begin(); it != histogramData.end(); it++)
    {        
		std::string key = std::format("{:03}", it->first);
        stringHistogramData.insert(std::pair<std::string, int>(key, it->second));
    }

    this->histogram(stringHistogramData, labelCount, fileName);
}

void MyEventReceiver::histogram(std::map<std::string, int> histogramData, int labelCount, std::string fileName)
{
    int n = histogramData.size();
    double* x = new double[n];
    const char** z = new const char* [n];

    int i = 0;
    std::map<std::string, int>::iterator it;
    for (it = histogramData.begin(); it != histogramData.end(); it++)
    {
        x[i] = it->second;
        z[i] = it->first.c_str();
        i++;
    }

    XYChart* c = new XYChart(300, 300);
    c->setPlotArea(50, 20, 240, 250);

    // Add a line chart layer using the given data
    c->addBarLayer(DoubleArray(x, n));

    // Set the labels on the x axis.
    c->xAxis()->setLabels(StringArray(z, n));

    // Display 1 out of 3 labels on the x-axis.
    double steps = ((double)n)/((double)labelCount);
    c->xAxis()->setLabelStep(steps);

    c->makeChart(fileName.c_str());

    //free up resources
    delete c;
    delete x;
    delete z;
}

void MyEventReceiver::diagram(std::vector<std::complex<double>> data, std::string fileName)
{
    int n = data.size();
    double* x = new double[n];
    double* y = new double[n];
    const char** z = new const char* [n];

    for (int i = 0; i < n; ++i)
    {
        y[i] = data[i].real();
        x[i] = data[i].imag();

        const char* label = this->stringSerivce->intToString(i).c_str();
        z[i] = label;
    }

    XYChart* c = new XYChart(300, 300);
    c->setPlotArea(50, 20, 240, 250);

    // Add a line chart layer using the given data
    c->addLineLayer(DoubleArray(x, n));
    c->addLineLayer(DoubleArray(y, n));

    // Set the labels on the x axis.
    c->xAxis()->setLabels(StringArray(z, n));

    // Display 1 out of 3 labels on the x-axis.
    c->xAxis()->setLabelStep(3);

    c->makeChart(fileName.c_str());

    //free up resources
    delete c;
    delete x;
    delete y;
    delete z;
}

void MyEventReceiver::diagram(std::vector<double> data, std::string fileName)
{
    int n = data.size();
    double* x = new double[n];
    const char** z = new const char* [n];

    for (int i = 0; i < n; ++i)
    {
        x[i] = data[i];

        const char* label = this->stringSerivce->intToString(i).c_str();
        z[i] = label;
    }

    XYChart* c = new XYChart(300, 300);
    c->setPlotArea(50, 20, 240, 250);

    // Add a line chart layer using the given data
    c->addLineLayer(DoubleArray(x, n));

    // Set the labels on the x axis.
    c->xAxis()->setLabels(StringArray(z, n));

    // Display 1 out of 3 labels on the x-axis.
    c->xAxis()->setLabelStep(3);

    c->makeChart(fileName.c_str());

    //free up resources
    delete c;
    delete x;
    delete z;
}