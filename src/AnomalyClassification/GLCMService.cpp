#include "GLCMService.h"

GLCMService::GLCMService(CImgService* imgService)
{
    this->imgService = imgService;
}

GLCMResult GLCMService::calculate(CImg<unsigned char>* image)
{
    float energy=0,contrast=0,homogenity=0,IDM=0,entropy=0,mean1=0;
    
    int row = image->width();
    int col = image->height();

    const unsigned int size_z = 1;
	const unsigned int size_c = 3;
    CImg<unsigned char> gl(256, 256, size_z, size_c, 0);
  
    unsigned int blackCounter = 0;
    unsigned int whiteCounter = 0;

    //creating glcm matrix with 256 levels,radius=1 and in the horizontal direction 
    for(int i=0;i<row;i++)
    {
        for(int j=0;j<col-1;j++)
        {
            ColorRGB colorX = this->imgService->getPixel(image, i,j);
            ColorRGB colorY = this->imgService->getPixel(image, i,j+1);
            ColorRGB currentColorGL = this->imgService->getPixel(&gl, colorX.r, colorY.r);

            if(colorX.r == 0)
            {
                blackCounter++;
            }
            else if(colorX.r == 255)
            {
                whiteCounter++;
            }

            if(currentColorGL.r < 255)
            {
                currentColorGL.r += 1;
                currentColorGL.g += 1;
                currentColorGL.b += 1;            
            }

            this->imgService->setPixel(&gl, colorX.r, colorY.r, currentColorGL);
        }
    }

    // normalizing glcm matrix for parameter determination
    this->imgService->normalizeGrayMatrix(&gl, whiteCounter, blackCounter, 1.0);
    gl = gl + this->imgService->transpose(&gl);
 
    for(int i=0;i<256;i++)
    {
        for(int j=0;j<256;j++)
        {
            ColorRGB colorIj = this->imgService->getPixel(&gl, i,j);

            energy= energy + colorIj.r * colorIj.r;            //finding parameters
            contrast=contrast+(i-j)*(i-j)*colorIj.r;
            homogenity=homogenity+colorIj.r/(1+abs(i-j));

            if(i!=j)
            {
                IDM=IDM+colorIj.r/((i-j)*(i-j));                      //Taking k=2;
            }

            if(colorIj.r!=0)
            {
                entropy=entropy-colorIj.r*log10(colorIj.r);
            }

            mean1=mean1+0.5*(i*colorIj.r+j*colorIj.r);
        }
    }
    
    return GLCMResult(energy, contrast, homogenity, IDM, entropy, mean1, gl);
}