#include "EdgeDetector.h"
#include "BMPPixel.h"
#include <sys/stat.h>
#include <errno.h>
#include <assert.h>
#include <cstdio>
#include <cstdlib>

#define MARK cout << "\tAt " << __LINE__ << endl;

using namespace std;

EdgeDetector::EdgeDetector()
: filename( "output_images/edged.bmp" ),  bmp( NULL ), outbmp(NULL), raw_edge_image( NULL )
{
    MakeOutputDir();
}

EdgeDetector::EdgeDetector( BMPImage *bmp )
: filename( "output_images/edged.bmp" ), bmp( bmp ), outbmp(NULL), raw_edge_image( NULL )
{
    this->filename = "output_images/" + bmp->GetFilename();
    MakeOutputDir();
}

void  EdgeDetector::SetOutputFilePath( std::string filename )
{
    this->filename = filename;
}

void EdgeDetector::DetectEdges()
{
    AllocateOutputImage();
    EdgeDetection();
    WriteBMP();
}

void EdgeDetector::EdgeDetection()
{
    cout << "!You are using a base class to perform edge detection, you must use one of the algorithm\
            classes to use this function!" << endl;
    
    exit(-1);
}

BMPImage* EdgeDetector::SetBMPimage( BMPImage *bmp )
{
    BMPImage *tmp = this->bmp;
    this->bmp = bmp;
    this->filename = "output_images/" + bmp->GetFilename();
    return tmp;         //to be freed if dynamically allocated
}

void EdgeDetector::MakeOutputDir()
{
    const int dir_err = mkdir("output_images", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    
    //detect errors in making output directory, ignore if it already exists
    if ( dir_err < 0 && errno != EEXIST )
        cout << "Error creating directory!" << endl;
}

bool EdgeDetector::WriteWhitePixel( int x, int y )
{
    if( outbmp->getPixelType() == _24BIT_RGB )
        return WritePixel( x, y, 0xFF, 0xFF, 0xFF );
    else
        return WritePixel( x, y, 0xFF );
}

bool EdgeDetector::WriteBlackPixel( int x, int y )
{
    if( outbmp->getPixelType() == _24BIT_RGB )
        return WritePixel( x, y, 0x00, 0x00, 0x00 );
    else
        return WritePixel( x, y, 0x00 );
}

bool EdgeDetector::WritePixel( int x, int y, unsigned char R, unsigned G, unsigned B )
{
    if( x < 0 || x > outbmp->getWidth() || y < 0 || y > outbmp->getHeight() )
    {
        return false;
    }
    else
    {
        RGBPixel24 *tmp = new RGBPixel24(R, G, B);
        outbmp->setPixel( x, y, tmp );
        delete tmp;
        
        return true;
    }
}

bool EdgeDetector::WritePixel( int x, int y, unsigned char grayscale )
{
    if( x < 0 || x > outbmp->getWidth() || y < 0 || y > outbmp->getHeight() )
    {
        return false;
    }
    else
    {
        GrayPixel8 *tmp = new GrayPixel8( grayscale );
        outbmp->setPixel( x, y, tmp );
        delete tmp;
        
        return true;
    }
}

void EdgeDetector::AllocateOutputImage()
{
    if( outbmp != NULL )
        delete outbmp;
    
    outbmp = new BMPImage( *bmp, filename );
}

void EdgeDetector::WriteBMP()
{
    outbmp->Write();
}








