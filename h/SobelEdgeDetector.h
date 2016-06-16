#ifndef __SOBELEDGEDETECTOR_H_
#define __SOBELEDGEDETECTOR_H_

#include "EdgeDetector.h"

#define THRESHOLD 120

#define SOBEL_DIM 3
#define SOBEL_COUNT 9

class SobelEdgeDetector : public EdgeDetector
{
public:
    SobelEdgeDetector();
    SobelEdgeDetector( BMPImage *bmp );
    virtual void EdgeDetection();
    
    static const int filter_x[SOBEL_DIM][SOBEL_DIM];
    static const int filter_y[SOBEL_DIM][SOBEL_DIM];
    
    unsigned int filterPixels( RGBPixel24 **pixels );
    unsigned int filterPixels( GrayPixel8 **pixels );
};

#endif
