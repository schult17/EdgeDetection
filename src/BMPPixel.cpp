#include "BMPPixel.h"

#define RGB_TO_GRAY(r, g, b) (unsigned int) 0.30*r + 0.59*g + 0.11*b;

//----------Base class----------//
BMPPixel::BMPPixel( PixelType type )
: type( type )
{}
//------------------------------//

//----------RGB pixels----------//
RGBPixel24::RGBPixel24()
: BMPPixel( _24BIT_RGB ), R(0x00), G(0x00), B(0x00)
{}

RGBPixel24::RGBPixel24( unsigned char R, unsigned char G, unsigned char B )
: BMPPixel( _24BIT_RGB ), R( R ), G( G ), B( B )
{}

unsigned int RGBPixel24::toGrayScale()
{
    return RGB_TO_GRAY( R, G, B );
}
//------------------------------//

//----------Gray Pixels----------//
GrayPixel8::GrayPixel8()
: BMPPixel( _8BIT_GRAY ), grayscale( 0 )
{}

GrayPixel8::GrayPixel8( unsigned char scale )
: BMPPixel( _8BIT_GRAY ), grayscale( scale )
{}
//-------------------------------//
