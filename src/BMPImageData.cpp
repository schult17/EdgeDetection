#include "BMPImageData.h"

using namespace std;

#define POS_MODULO(a, b) (a%b+b)%b

BMPImageData::BMPImageData( FillMode mode )
: height( 0 ), width( 0 ), bitsPerPixel( 0 ), rowSize( 0 ), pixelArraySize( 0 ), data( NULL ), fillMode( mode )
{}

BMPImageData::BMPImageData( int height, int width, int bitsPerPixel, int rowSize, int pixelArraySize, unsigned char *data, FillMode mode )
: height( height ), width( width ), bitsPerPixel( bitsPerPixel ),
rowSize( rowSize ), pixelArraySize( pixelArraySize ), data( data ), fillMode( mode )
{}

BMPImageData::BMPImageData( const BMPImageData &cpy )
{
    width = cpy.width;
    height = cpy.height;
    bitsPerPixel = cpy.bitsPerPixel;
    
    rowSize = cpy.rowSize;
    pixelArraySize = cpy.pixelArraySize;
    
    data = new unsigned char[pixelArraySize];
    memcpy( data, cpy.data, pixelArraySize );
    
    fillMode = cpy.fillMode;
}

BMPImageData::~BMPImageData()
{
    if( data != NULL )  delete data;
}

BMPImageData & BMPImageData::operator=( const BMPImageData &rhs )
{
    width = rhs.width;
    height = rhs.height;
    bitsPerPixel = rhs.bitsPerPixel;
    
    rowSize = rhs.rowSize;
    pixelArraySize = rhs.pixelArraySize;
    
    delete data;
    data = new unsigned char[pixelArraySize];
    
    memcpy( data, rhs.data, pixelArraySize );
    
    return *this;
}

void BMPImageData::setData( int height, int width, int bitsPerPixel, int rowSize, int pixelArraySize, unsigned char *data )
{
    this->height = height;
    this->width = width;
    this->bitsPerPixel = bitsPerPixel;
    this->rowSize = rowSize;
    this->pixelArraySize = pixelArraySize;
    
    if( this->data != NULL ) delete data;
    this->data = data;
}

void BMPImageData::ClearData( int clear_val )
{
    memset( data, clear_val, pixelArraySize );
}

BMPPixel BMPImageData::getPixel( int x, int y )
{
    y = height - 1 - y;     //must flip Y
    
    if( x >= 0 && x <= width && y >= 0 && y <= height )
    {
        int pixel_base = rowSize * y + RGB_PIXEL_WIDTH * x;
        
        unsigned char R, G, B;
        R = data[pixel_base + 2];
        G = data[pixel_base + 1];
        B = data[pixel_base];
        
        return BMPPixel( R, G, B );
    }
    else        //useful for edge detection, return black outside image
    {
        switch( fillMode )
        {
            case Wrap:
            {
                if( x > width || x < 0 )
                    x = POS_MODULO(x, width);
                
                if( y > height || y < 0 )
                    y = POS_MODULO(x, height);
                
                int pixel_base = rowSize * y + RGB_PIXEL_WIDTH * x;
                
                unsigned char R, G, B;
                R = data[pixel_base + 2];
                G = data[pixel_base + 1];
                B = data[pixel_base];
                
                return BMPPixel( R, G, B );
            }
            case White:
            {
                return BMPPixel( 0xFF, 0xFF, 0xFF );
            }
            case Black:
            {
                return BMPPixel( 0x00, 0x00, 0x00 );
            }
            case Null:
            default:
            {
                return BMPPixel();
            }
        }
    }
}

void BMPImageData::setPixel( int x, int y, BMPPixel pixel )
{
    y = height - 1 - y;         //flipping
    
    //editing data in pixelData array
    int pixel_base = rowSize * y + RGB_PIXEL_WIDTH * x;
    data[pixel_base + 2] = pixel.R;
    data[pixel_base + 1] = pixel.G;
    data[pixel_base] = pixel.B;
}
