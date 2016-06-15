#include "BasicEdgeDetector.h"
#include "BMPPixel.h"
#include <vector>

using namespace std;

BasicEdgeDetector::BasicEdgeDetector() : EdgeDetector()
{
    one_direction_detector_called = false;
}

BasicEdgeDetector::BasicEdgeDetector( BMPImage *bmp ) : EdgeDetector( bmp )
{
    one_direction_detector_called = false;
}

void BasicEdgeDetector::EdgeDetection()
{
    cout << "\tBeginning \"Basic\" edge detection algorithm" << endl;
    
    HorizontalEdges();
    VerticalEdges();
    one_direction_detector_called = false;
    
    cout << "\tFinished \"Basic\" edge detection algorithm" << endl;
}

void BasicEdgeDetector::FindEdges(bool horizontal)
{
    bool set_non_edge_pixels_black = true;
    int w = bmp->getWidth();
    int h = bmp->getHeight();
    BMPPixel *p1, *p2;
    
    int Bmin = 300;
    int Bmax = -300;
    
    int diff;
    
    //Finding the min and max difference in gray scale value
    for( int x = (horizontal ? 0:1); x < w - (horizontal ? 0:1); x++ )
    {
        for( int y = (!horizontal ? 0:1); y < h - (!horizontal ? 0:1); y++ )
        {
            p1 = bmp->getPixel( x-(horizontal ? 0:1), y-(!horizontal ? 0:1) );
            p2 = bmp->getPixel( x+(horizontal ? 0:1), y+(!horizontal ? 0:1) );
            
            if( p1->type == _24BIT_RGB)
                diff = ((RGBPixel24 *)p2)->toGrayScale() - ((RGBPixel24 *)p1)->toGrayScale();
            else    //8 bit gray scale
                diff = ((GrayPixel8 *)p2)->grayscale - ((GrayPixel8 *)p1)->grayscale;
            
            if( diff < Bmin )
                Bmin = diff;
            
            if( diff > Bmax )
                Bmax = diff;
            
            delete p1;
            delete p2;
            p1 = p2 = NULL;
        }
    }
    
    //calculating gradient to find edges
    for( int x = (horizontal ? 0:1); x < w - (horizontal ? 0:1); x++ )
    {
        for( int y = (!horizontal ? 0:1); y < h - (!horizontal ? 0:1); y++ )
        {
            p1 = bmp->getPixel( x-(horizontal ? 0:1), y-(!horizontal ? 0:1) );
            p2 = bmp->getPixel( x+(horizontal ? 0:1), y+(!horizontal ? 0:1) );
        
            if( p1->type == _24BIT_RGB)
                diff = ((RGBPixel24 *)p2)->toGrayScale() - ((RGBPixel24 *)p1)->toGrayScale();
            else    //8 bit gray scale
                diff = ((GrayPixel8 *)p2)->grayscale - ((GrayPixel8 *)p1)->grayscale;
            
            diff = (((float)diff - (float)Bmin)/((float)Bmax - (float)Bmin)) * 255.0;
                
            
            if( diff < THRESHOLD )
            {
                WriteWhitePixel( x, y );
            }
            else
            {
                //This is to init black pixels, only want to do
                //in one direction, both would overwrite some previous pixels
                if( !one_direction_detector_called )
                {
                    WriteBlackPixel( x, y );
                    set_non_edge_pixels_black = true;
                }
            }
            
            delete p1;
            delete p2;
            p1 = p2 = NULL;
        }
    }
    
    one_direction_detector_called = set_non_edge_pixels_black;
}

void BasicEdgeDetector::HorizontalEdges()
{
    FindEdges( true );
}

void BasicEdgeDetector::VerticalEdges()
{
    FindEdges( false );
}
