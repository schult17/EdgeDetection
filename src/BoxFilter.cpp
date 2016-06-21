#include <iostream>
#include <cmath>
#include "BoxFilter.h"

using namespace std;

BoxFilter::BoxFilter( BMPImage *bmpimage, int radius )
: Filter( bmpimage ), radius( max(radius, 1) )
{}

BoxFilter::BoxFilter( BMPImageData *bmp, int radius )
: Filter( bmp ), radius( max(radius, 1) )
{}

void BoxFilter::ApplyFilter()
{
    cout << "\tApplying Box filter" << endl;
    
    int w = Width();
    int h = Height();
    
    int DIM = radius*2 + 1;
    int COUNT = DIM * DIM;
    
    BMPPixel *pixels = new BMPPixel[COUNT];
    
    for( int x = radius; x < w - (radius + 1); x++ )
    {
        for( int y = radius; y < h - (radius + 1); y++ )
        {
            for( int i = 0; i < COUNT; i++ )
                pixels[i] = getPixel( (x-1)+(i%DIM), (y-1)+(i/DIM) );
            
            filterPixels( x, y, DIM, pixels );
        }
    }
    
    cout << "\tFinished Box filtering" << endl;
}

//TODO -- Filter border pixels??

void BoxFilter::filterPixels( int x, int y, int DIM, BMPPixel *pixels )
{
    int r = 0, g = 0, b = 0;
    
    for( int i = 0; i < DIM; i++ )
    {
        for( int j = 0; j < DIM; j++ )
        {
            r += (pixels[i * DIM + j]).R & 0xff;
            g += (pixels[i * DIM + j]).G & 0xff;
            b += (pixels[i * DIM + j]).B & 0xff;
        }
    }
    
    r = min( (int)round((double)r/(double)(DIM*DIM)), 255 );
    g = min( (int)round((double)g/(double)(DIM*DIM)), 255 );
    b = min( (int)round((double)b/(double)(DIM*DIM)), 255 );
    
    WritePixel( x, y, r, g, b );
}
