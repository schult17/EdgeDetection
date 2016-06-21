#include <iostream>
#include <cmath>
#include "BoxFilter.h"

using namespace std;

//TODO -- make this seperable??
void BoxFilter::ApplyFilter()
{
    cout << "\tApplying Box filter" << endl;
    
    int w = Width();
    int h = Height();
    
    int DIM = radius*2 + 1;
    int COUNT = DIM * DIM;
    
    BMPPixel *pixels = new BMPPixel[COUNT];
    
    //Out of range pixels will be Null, and won't count towards weighting
    //as long as the wrap mode of the bmp is set to BMPImageData::Null
    for( int x = 0; x < w; x++ )
    {
        for( int y = 0; y < h; y++ )
        {
            for( int i = 0; i < COUNT; i++ )
                pixels[i] = getPixel( (x-radius)+(i%DIM), (y-radius)+(i/DIM) );
            
            filterPixels( x, y, DIM, pixels );
        }
    }
    
    delete pixels;
    
    cout << "\tFinished Box filtering" << endl;
}

void BoxFilter::filterPixels( int x, int y, int DIM, BMPPixel *pixels )
{
    int r = 0, g = 0, b = 0;
    
    double count = 0;
    
    for( int i = 0; i < DIM; i++ )
    {
        for( int j = 0; j < DIM; j++ )
        {
            if( !pixels[i * DIM + j].isNull() )
            {
                r += (pixels[i * DIM + j]).R & 0xff;
                g += (pixels[i * DIM + j]).G & 0xff;
                b += (pixels[i * DIM + j]).B & 0xff;
                
                count += 1;
            }
        }
    }
    
    r = min( (int)round((double)r/count), 255 );
    g = min( (int)round((double)g/count), 255 );
    b = min( (int)round((double)b/count), 255 );
    
    WritePixel( x, y, r, g, b );
}

