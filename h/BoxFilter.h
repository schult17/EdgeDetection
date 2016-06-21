#ifndef __BOXFILTER_H_
#define __BOXFILTER_H_

#include "Filter.h"

#define DEFAULT_RADIUS 1

class BoxFilter : public Filter
{
public:
    BoxFilter( BMPImage *bmpimage, int radius = DEFAULT_RADIUS );
    BoxFilter( BMPImageData *bmp, int radius = DEFAULT_RADIUS );
    
    virtual void ApplyFilter();
    
    void SetRadius( int radius ){ std::max(radius, 3); }
    
private:
    void filterPixels( int x, int y, int DIM, BMPPixel *pixels );
    int radius;
};

#endif
