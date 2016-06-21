#ifndef __BMPIMAGEDATA_H_
#define __BMPIMAGEDATA_H_

#include "BMPPixel.h"
#include <iostream>

#define RGB_PIXEL_WIDTH 3

class BMPImageData
{
public:
    enum FillMode{ Wrap, Black, White, Null };
    
    BMPImageData( FillMode mode = Wrap );
    BMPImageData( int height, int width, int bitsPerPixel, int rowSize, int pixelArraySize, unsigned char *data, FillMode mode = Null );
    BMPImageData( const BMPImageData &cpy );
    ~BMPImageData();
    
    void setData( int height, int width, int bitsPerPixel, int rowSize, int pixelArraySize, unsigned char *data );
    
    void ClearData( int clear_val );
    
    int getWidth(){ return width; }
    int getHeight(){ return height; }
    int getBitsPerPixel(){ return bitsPerPixel; }
    int getRowSize(){ return rowSize; }
    int getArraySize(){ return pixelArraySize; }
    
    BMPPixel getPixel( int x, int y );
    unsigned char * getPixelData(){ return data; }
    
    void setPixel( int x, int y, BMPPixel pixel );
    void swapPixelData( unsigned char *new_data );
    void setFillMode( FillMode mode ) { fillMode = mode; }
    
    BMPImageData & operator=( const BMPImageData &rhs );
    
private:
    int height;
    int width;
    int bitsPerPixel;
    int rowSize;
    int pixelArraySize;
    
    unsigned char *data;
    
    FillMode fillMode;
};

#endif
