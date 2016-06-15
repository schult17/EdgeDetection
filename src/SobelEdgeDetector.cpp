#include "SobelEdgeDetector.h"
#include "BMPPixel.h"

using namespace std;

SobelEdgeDetector::SobelEdgeDetector()
: EdgeDetector()
{}

SobelEdgeDetector::SobelEdgeDetector( BMPImage *bmp )
: EdgeDetector( bmp )
{}

void SobelEdgeDetector::EdgeDetection()
{
    cout << "\tBeginning Sobel edge detection algorithm" << endl;
    
    //TODO -- do the edge detection
    
    cout << "\tFinished Sobel edge detection algorithm" << endl;
}
