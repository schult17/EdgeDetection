#include "BMPPixel.h"
#include <iostream>

#define RGB_TO_GRAY(r, g, b) (unsigned int) 0.30*r + 0.59*g + 0.11*b;

BMPPixel::BMPPixel()
: R(0x00), G(0x00), B(0x00), Null( true )
{}

BMPPixel::BMPPixel( unsigned char R, unsigned char G, unsigned char B )
: R( R ), G( G ), B( B ), Null( false )
{}

BMPPixel::BMPPixel( unsigned char gray )
: R( gray ), G( gray ), B( gray ), Null( false )
{}

unsigned int BMPPixel::toGrayScale()
{
    return RGB_TO_GRAY( R, G, B );
}
