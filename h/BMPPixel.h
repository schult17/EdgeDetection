#ifndef __BMPPIXEL_H_
#define __BMPPIXEL_H_

enum PixelType{ _8BIT_GRAY, _24BIT_RGB, UNKWN };

class BMPPixel
{
public:
    BMPPixel( PixelType type );
    PixelType type;
};

class RGBPixel24 : public BMPPixel
{
public:
    RGBPixel24();
    RGBPixel24( unsigned char R, unsigned char G, unsigned char B );
    
    unsigned int toGrayScale();
    
    unsigned char R;
    unsigned char G;
    unsigned char B;
};

class GrayPixel8 : public BMPPixel
{
public:
    GrayPixel8();
    GrayPixel8( unsigned char scale );
    
    unsigned char grayscale;
};

#endif
