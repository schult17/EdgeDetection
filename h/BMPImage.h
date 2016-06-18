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
    BMPImage( const BMPImage &cpy, std::string filename );
    BMPImage( const BMPImage &cpy, std::string filename, int init_val );
    ~BMPImage();
    
    void Remove();
    
    int getWidth(){ return pixelData->getWidth(); }
    int getHeight(){ return pixelData->getHeight(); }
    std::string GetFilename();
    std::string GetFilepath(){ return filename; }
    BMPPixel getPixel( int x, int y ){ return pixelData->getPixel( x, y ); }
    BMPImageData getPixelData();
    
    void SetFilename(){ this->filename = filename; }
    void writePixel( int x, int y, std::fstream &file );
    void setPixel( int x, int y, BMPPixel pixel ){ pixelData->setPixel( x, y, pixel ); }
    
    void swapPixelData( unsigned char *new_data ){ pixelData->swapPixelData( new_data ); }
    
    void Write();
    
    static bool out_of_bounds_pixel_read;
    
private:
    void Read();
    
    void onCopy( const BMPImage &cpy, std::string filename, int *init_val );
    
    unsigned char bmpFileHeader[FILE_HEADER_SIZE];
    unsigned char pixelArrayOffset;
    unsigned char bmpInfoHeader[INFO_HEADER_SIZE];
    
    BMPImageData *pixelData;
    
    std::string filename;
};


#endif

