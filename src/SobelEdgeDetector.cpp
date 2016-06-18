#include "SobelEdgeDetector.h"
#include "BMPPixel.h"
#include "BoxFilter.h"
#include <cmath>

using namespace std;

//initialize static members : these are the Sobel filters
const int SobelEdgeDetector::filter_x[SOBEL_DIM][SOBEL_DIM] = {{-1, 0, 1},
                                                               {-2, 0, 2},
                                                               {-1, 0, 1} };

const int SobelEdgeDetector::filter_y[SOBEL_DIM][SOBEL_DIM] = {{-1, -2, -1},
                                                               {0, 0, 0},
                                                               {1, 2, 1} };

SobelEdgeDetector::SobelEdgeDetector()
: EdgeDetector()
{}

SobelEdgeDetector::SobelEdgeDetector( BMPImage *bmp )
: EdgeDetector( bmp )
{}

void SobelEdgeDetector::EdgeDetection()
{
    cout << "\tBeginning Sobel edge detection algorithm" << endl;
    
    /*
    BoxFilter f( bmp );
    f.Filter();
     */
    
    int w = bmp->getWidth();
    int h = bmp->getHeight();
    
    /*
    // testing with Box Filter
    BMPPixel p;
    for( int x = 0; x < w; x++ )
    {
        for( int y = 0; y < h; y++ )
        {
            p = bmp->getPixel( x, y );
            WritePixel( x, y, p.R, p.G, p.B );
        }
    }
    
    bmp->swapPixelData( f.outbmp->getPixelData() );
    //---------//
     */
    
    unsigned int gray_pixel_val = 0;
    
    BMPPixel pixels[SOBEL_COUNT];
    
    for( int x = 1; x < w-2; x++ )
    {
        for( int y = 1; y < h-2; y++ )
        {
            //Get the 9 pixels
            for( int i = 0; i < SOBEL_COUNT; i++ )
                pixels[i] = bmp->getPixel( (x-1)+(i%SOBEL_DIM), (y-1)+(i/SOBEL_DIM) );
            
            //Get the gray scale value
            gray_pixel_val = filterPixels( pixels );
            
            //Write the gray scale value
            WritePixel( x, y, gray_pixel_val );
        }
    }
    
    cout << "\tFinished Sobel edge detection algorithm" << endl;
}

unsigned int SobelEdgeDetector::filterPixels( BMPPixel *pixels )
{
    int px = 0, py = 0;
    
    for( int x = 0; x < SOBEL_DIM; x++ )
    {
        for( int y = 0; y < SOBEL_DIM; y++ )
        {
            px += filter_x[x][y] * (pixels[y * SOBEL_DIM + x]).toGrayScale();
            py += filter_y[x][y] * (pixels[y * SOBEL_DIM + x]).toGrayScale();
        }
    }
    
    px /= 4;
    py /= 4;
    
    return sqrt( px*px + py*py );       //round?
}












