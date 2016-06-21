#ifndef __JPEGIMAGE_H_
#define __JPEGIMAGE_H_

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "BMPPixel.h"
#include "BMPImageData.h"

#define FILE_HEADER_SIZE 14
#define INFO_HEADER_SIZE 40

#define INFO_WIDTH_OFFSET 4
#define INFO_HEIGHT_OFFSET 8
#define INFO_BITS_PER_PIXEL_OFFSET 14
#define INFO_COMPRESSION_OFFSET 16


class BMPImage
{
public:
    BMPImage( std::string filename );
    
    BMPImage( const BMPImage &cpy );
    BMPImage( const BMPImage &cpy, std::string filename = "output.bmp" );
    BMPImage( const BMPImage &cpy, std::string filename = "output.bmp", BMPImageData * cpyData = NULL );
    ~BMPImage();
    
    int getWidth(){ return pixelData->getWidth(); }
    int getHeight(){ return pixelData->getHeight(); }
    std::string GetFilename();
    std::string GetFilepath(){ return filename; }
    BMPPixel getPixel( int x, int y ) { return pixelData->getPixel( x, y ); }
    BMPImageData * getPixelData() { return pixelData; }
    
    void SetFilename(){ this->filename = filename; }
    void setPixel( int x, int y, BMPPixel pixel ){ pixelData->setPixel( x, y, pixel ); }
    void setWrapMode( BMPImageData::FillMode mode ) { pixelData->setFillMode( mode ); }
    
    void swapPixelData( BMPImageData *newData );
    
    void Write();
    
    static bool out_of_bounds_pixel_read;
    
private:
    void Read();
    void OnCopy( const BMPImage &cpy );
    void WriteHeaders( std::ofstream &file );
    void WritePixel( int x, int y, std::ofstream &file );
    
    unsigned char bmpFileHeader[FILE_HEADER_SIZE];
    unsigned char pixelArrayOffset;
    unsigned char bmpInfoHeader[INFO_HEADER_SIZE];
    unsigned char *padding;
    int paddingSize;
    
    BMPImageData *pixelData;
    
    std::string filename;
};


#endif

