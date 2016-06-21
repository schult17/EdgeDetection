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

void SobelEdgeDetector::ApplyFilter()
{
    cout << "\tBeginning Sobel edge detection algorithm" << endl;
    
    int w = Width();
    int h = Height();
    
    unsigned int gray_pixel_val = 0;
    
    BMPPixel pixels[SOBEL_COUNT];
    
    //Note: If the wrap mode of the BMPImageData is set to BMPImageData::Null, getPixel()
    //will return a 'NULL' BMPPixel, so going beyond the bounds is not a problem
    //(Before we used x = 1, x < w - 1 and y = 1, y < h - 1)
    for( int x = 0; x < w; x++ )
    {
        for( int y = 0; y < h; y++ )
        {
            //Get the 9 pixels
            for( int i = 0; i < SOBEL_COUNT; i++ )
                pixels[i] = getPixel( (x-1)+(i%SOBEL_DIM), (y-1)+(i/SOBEL_DIM) );
            
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
    int offset = 0;
    
    for( int x = 0; x < SOBEL_DIM; x++ )
    {
        for( int y = 0; y < SOBEL_DIM; y++ )
        {
            offset = y * SOBEL_DIM + x;
            if( !pixels[offset].isNull() )
            {
                px += filter_x[x][y] * pixels[offset].toGrayScale();
                py += filter_y[x][y] * pixels[offset].toGrayScale();
            }
        }
    }
    
    //got rid of px /= 4, py /= 4 here, not supposed to be there?
    
    //return max( (abs(px) + abs(px)), 255 );   //approximation of sqrt(px^2, py^2), faster
    return max( sqrt(px*px + py*py), 255 );
}












