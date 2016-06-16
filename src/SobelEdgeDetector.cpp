#include "SobelEdgeDetector.h"
#include "BMPPixel.h"
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
    
    int w = bmp->getWidth();
    int h = bmp->getHeight();
    
    unsigned int gray_pixel_val = 0;
    
    bool rgb24bit = (bmp->getPixelType() == _24BIT_RGB);
    
    BMPPixel *pixels[SOBEL_COUNT];
    
    for( int x = 1; x < w-2; x++ )
    {
        for( int y = 1; y < h-2; y++ )
        {
           
            //Get the 9 pixels
            for( int i = 0; i < SOBEL_COUNT; i++ )
                pixels[i] = bmp->getPixel( (x-1)+(i%SOBEL_DIM), (y-1)+(i/SOBEL_DIM) );
            
            //Get the gray scale value
            gray_pixel_val = rgb24bit ? filterPixels( (RGBPixel24**)pixels )
                                    : filterPixels( (GrayPixel8**)pixels );
            
            //Write the gray scale value
            rgb24bit ? WritePixel( x, y, gray_pixel_val, gray_pixel_val, gray_pixel_val )
                     : WritePixel( x, y, gray_pixel_val );
        }
        
        //free the nine pixels
        for( int i = 0; i < SOBEL_COUNT; i++ )
            delete pixels[i];
    }
    
    //WriteBlackBorder();
    
    cout << "\tFinished Sobel edge detection algorithm" << endl;
}

unsigned int SobelEdgeDetector::filterPixels( RGBPixel24 **pixels )
{
    //TODO -- divide px and py by 4 after for loops?
    int px = 0, py = 0;
    
    for( int x = 0; x < SOBEL_DIM; x++ )
    {
        for( int y = 0; y < SOBEL_DIM; y++ )
        {
            px += filter_x[x][y] * (pixels[y * SOBEL_DIM + x])->toGrayScale();
            py += filter_y[x][y] * (pixels[y * SOBEL_DIM + x])->toGrayScale();
        }
    }
    
    px /= 4;
    py /= 4;
    
    return sqrt( px*px + py*py );
}

unsigned int SobelEdgeDetector::filterPixels( GrayPixel8 **pixels )
{
    //TODO -- divide px and py by 4 after for loops?
    int px = 0, py = 0;
    
    for( int x = 0; x < SOBEL_DIM; x++ )
    {
        for( int y = 0; y < SOBEL_DIM; y++ )
        {
            px += filter_x[x][y] * (pixels[y * SOBEL_DIM + x])->grayscale;
            py += filter_y[x][y] * (pixels[y * SOBEL_DIM + x])->grayscale;
        }
    }
    
    px /= 4;
    py /= 4;
    
    return sqrt( px*px + py*py );
}












