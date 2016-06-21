#ifndef __FILTER_H_
#define __FILTER_H_

#include "BMPImage.h"
#include "BMPImageData.h"

class Filter
{
public:
    Filter( BMPImageData *indata );
    Filter( BMPImage *inimage );
    ~Filter();
    
    BMPImageData * GetOutputData() { return outdata; }
    void SwapInputOutputData();
    void ClearOutputData( int clear_val );
    void SwapAndClear( int clear_val );
    
protected:
    virtual void ApplyFilter();
    
    bool WriteWhitePixel( int x, int y );
    bool WriteBlackPixel( int x, int y );
    bool WritePixel( int x, int y, unsigned char R, unsigned G, unsigned B );
    bool WritePixel( int x, int y, unsigned char grayscale );
    BMPPixel getPixel( int x, int y ){ return indata->getPixel( x, y ); }
    int Height() { return indata->getHeight(); }
    int Width() { return indata->getWidth(); }
    
    BMPImageData *indata;
    BMPImageData *outdata;
};

#endif
