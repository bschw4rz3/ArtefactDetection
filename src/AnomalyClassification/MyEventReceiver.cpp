#include "MyEventReceiver.h"

MyEventReceiver::MyEventReceiver(GraphicEngineExtended* graphicEngine, SuperPixelService* superPixelService, ClassicSobelOperatorService* sobelOperatorSerivce, ImprovedSobelOperatorService* improvedSobelOperatorService, GeometricService* geometricService, HistogramValueService* histogramValueService, DiscreteFourierTransformationSerivce* discreteFourierTransformationSerivce, HuMomentsService* huMomentsService, DirectoryService* directoryService, StringSerivce* stringSerivce)
{
    this->graphicEngine = graphicEngine;
    this->superPixelService = superPixelService;
    this->sobelOperatorSerivce = sobelOperatorSerivce;
    this->improvedSobelOperatorService = improvedSobelOperatorService;
    this->geometricService = geometricService;
    this->histogramValueService = histogramValueService;
    this->discreteFourierTransformationSerivce = discreteFourierTransformationSerivce;
    this->huMomentsService = huMomentsService;

    this->stringSerivce = stringSerivce;
    this->directoryService = directoryService;

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
}

void MyEventReceiver::onDiscreteFourierTransformation()
{
    std::string cFile = this->stringSerivce->toString(this->selectedFile);
    CImg<unsigned char> img(cFile.c_str());

    std::vector<std::complex<double>> dftResult = this->discreteFourierTransformationSerivce->calculate(&img, 2000);

    int n = dftResult.size();
    double* x = new double[n];
    double* y = new double[n];
    const char ** z = new const char*[n];

    for (int i = 0; i < n; ++i) 
    {
        x[i] = dftResult[i].real();
        y[i] = dftResult[i].imag();

        const char * label = this->stringSerivce->intToString(i).c_str();
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

    // Output the chart
    std::string fileName = this->generateFileName();
    c->makeChart(fileName.c_str());

    this->graphicEngine->addImage(GUI_ID_IMAGE_3, Point2D(10, 10), this->stringSerivce->toWString(fileName).c_str(), GUI_ID_IMAGE_3_TAB);

    //free up resources
    delete c;
    delete x;
    delete y;
    delete z;

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

    int blackPixels = this->geometricService->countDefectPixels(&img, backgroundColor);
    int withePixels =  ((double)img.width()) * ((double)img.height()) - blackPixels;
    std::wstring blackPixelsString = this->stringSerivce->intToWString(blackPixels);
    std::wstring withePixelsString = this->stringSerivce->intToWString(withePixels);
    std::wstring blackPixelsStringUnit = blackPixelsString + std::wstring(L" px");
    std::wstring withePixelsStringUnit = withePixelsString + std::wstring(L" px");
    this->graphicEngine->setGUIElementText(GUI_ID_VALUE_AREA, std::wstring(L"W:"+withePixelsStringUnit+L"/B:"+blackPixelsStringUnit).c_str());

    double rotioRoiArea = ((double)img.width()) * ((double)img.height()) / ((double)blackPixels);
    std::wstring rotioRoiAreaString = this->stringSerivce->doubleToWString(rotioRoiArea);
    this->graphicEngine->setGUIElementText(GUI_ID_VALUE_RATIO_AREA_ROI, rotioRoiAreaString.c_str());

    double rotioWidthLength = ((double)img.width()) / ((double)img.height());
    std::wstring rotioWidthLengthString = this->stringSerivce->doubleToWString(rotioWidthLength);
    this->graphicEngine->setGUIElementText(GUI_ID_VALUE_RATIO_WIDTH_LENGTH, rotioWidthLengthString.c_str());

    int scope = this->geometricService->calculateScope(&img, backgroundColor);
    std::wstring scropWithUnit = this->stringSerivce->doubleToWString(scope) + L" px";
    this->graphicEngine->setGUIElementText(GUI_ID_VALUE_SCOPE, scropWithUnit.c_str());

    Point2D defectFocus = this->geometricService->calculateDefectFocus(&img, backgroundColor);
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