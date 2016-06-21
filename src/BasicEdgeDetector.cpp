#include "BasicEdgeDetector.h"
#include "BMPPixel.h"

using namespace std;

BasicEdgeDetector::BasicEdgeDetector( BMPImage *bmpimage )
: Filter( bmpimage ), one_direction_detector_called( false )
{}

BasicEdgeDetector::BasicEdgeDetector( BMPImageData *bmp )
: Filter( bmp ), one_direction_detector_called( false )
{}

void BasicEdgeDetector::ApplyFilter()
{
    cout << "\tBeginning Basic edge detection algorithm" << endl;
    
    HorizontalEdges();
    VerticalEdges();
    one_direction_detector_called = false;
    
    cout << "\tFinished Basic edge detection algorithm" << endl;
}

void BasicEdgeDetector::FindEdges(bool horizontal)
{
    bool set_non_edge_pixels_black = true;
    int w = Width();
    int h = Height();
    BMPPixel p1, p2;
    
    int Bmin = 300;
    int Bmax = -300;
    
    int diff;
    
    for( int x = (horizontal ? 0:1); x < w - (horizontal ? 0:1); x++ )
    {
        for( int y = (!horizontal ? 0:1); y < h - (!horizontal ? 0:1); y++ )
        {
            p1 = getPixel( x-(horizontal ? 0:1), y-(!horizontal ? 0:1) );
            p2 = getPixel( x+(horizontal ? 0:1), y+(!horizontal ? 0:1) );
            
            diff = p2.toGrayScale() - p1.toGrayScale();
            
            if( diff < Bmin )
                Bmin = diff;
            
            if( diff > Bmax )
                Bmax = diff;
        }
    }
    
    //calculating gradient to find edges
    for( int x = (horizontal ? 0:1); x < w - (horizontal ? 0:1); x++ )
    {
        for( int y = (!horizontal ? 0:1); y < h - (!horizontal ? 0:1); y++ )
        {
            p1 = getPixel( x-(horizontal ? 0:1), y-(!horizontal ? 0:1) );
            p2 = getPixel( x+(horizontal ? 0:1), y+(!horizontal ? 0:1) );
        
            diff = p2.toGrayScale() - p1.toGrayScale();
            
            //Normalizing by min and max difference value already calculated (always +)
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
        }
    }
    
    one_direction_detector_called = set_non_edge_pixels_black;
}

void BasicEdgeDetector::HorizontalEdges()
{
    cout << "\t\tFinding horizontal edges" << endl;
    FindEdges( true );
}

void BasicEdgeDetector::VerticalEdges()
{
    cout << "\t\tFinding vertical edges" << endl;
    FindEdges( false );
}
