#ifndef __SOBELEDGEDETECTOR_H_
#define __SOBELEDGEDETECTOR_H_

#include "Filter.h"

#define SOBEL_DIM 3
#define SOBEL_COUNT 9

class SobelEdgeDetector : public Filter
{
public:
    SobelEdgeDetector( BMPImage *bmpimage );
    SobelEdgeDetector( BMPImageData *bmp );
    virtual void ApplyFilter();
    
private:
    unsigned int filterPixels( BMPPixel *pixels );
    
    static const int filter_x[SOBEL_DIM][SOBEL_DIM];
    static const int filter_y[SOBEL_DIM][SOBEL_DIM];
};

#endif
