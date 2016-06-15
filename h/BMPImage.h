#ifndef __JPEGIMAGE_H_
#define __JPEGIMAGE_H_

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "BMPPixel.h"

#define FILE_HEADER_SIZE 14
#define INFO_HEADER_SIZE 40

#define INFO_WIDTH_OFFSET 4
#define INFO_HEIGHT_OFFSET 8
#define INFO_BITS_PER_PIXEL_OFFSET 14
#define INFO_COMPRESSION_OFFSET 16

#define RGB_PIXEL_WIDTH 3
#define GRAY_PIXEL_WIDTH 1

class BMPImage
{
public:
	BMPImage( std::string filename );
    BMPImage( const BMPImage &cpy );
    BMPImage( const BMPImage &cpy, std::string filename );
	~BMPImage();
    
    void Remove();
    
    int getWidth(){ return width; }
    int getHeight(){ return height; }
    std::string GetFilename();
    std::string GetFilepath(){ return filename; }
    BMPPixel * getPixel( int x, int y );
    PixelType getPixelType(){ return type; }
    
    void SetFilename(){ this->filename = filename; }
    void writePixel( int x, int y, std::fstream &file );
    void setPixel( int x, int y, BMPPixel *pixel );
    
    void Write();

private:
    void Read();
    
    unsigned char bmpFileHeader[FILE_HEADER_SIZE];
    unsigned char pixelArrayOffset;
    unsigned char bmpInfoHeader[INFO_HEADER_SIZE];
    
    int height;
    int width;
    int bitsPerPixel;
    
    int rowSize;
    int pixelArraySize;
    
    unsigned char *pixelData;
    
    std::string filename;
    
    PixelType type;
};

#endif

