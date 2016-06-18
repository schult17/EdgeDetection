#include "EdgeDetector.h"
#include "BMPPixel.h"
#include <sys/stat.h>
#include <errno.h>
#include <assert.h>
#include <cstdio>
#include <cstdlib>

//TODO -- Robinson compass
//TODO -- Box smoothing
//TODO -- Gaussian Smoothing

using namespace std;

EdgeDetector::EdgeDetector()
: filename( "output_images/edged.bmp" ),  bmp( NULL ), outbmp(NULL)
{
    MakeOutputDir();
}

EdgeDetector::EdgeDetector( BMPImage *bmp )
: filename( "output_images/edged.bmp" ), bmp( bmp ), outbmp(NULL)
{
    this->filename = "output_images/" + bmp->GetFilename();
    MakeOutputDir();
}

EdgeDetector::~EdgeDetector()
{
    if( outbmp != NULL )
        delete outbmp;
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
    return WritePixel( x, y, 0xFF, 0xFF, 0xFF );
}

bool EdgeDetector::WriteBlackPixel( int x, int y )
{
    return WritePixel( x, y, 0x00, 0x00, 0x00 );
}

bool EdgeDetector::WritePixel( int x, int y, unsigned char R, unsigned G, unsigned B )
{
    if( x < 0 || x > outbmp->getWidth() || y < 0 || y > outbmp->getHeight() )
    {
        return false;
    }
    else
    {
        outbmp->setPixel( x, y, BMPPixel(R, G, B) );
        return true;
    }
}

bool EdgeDetector::WritePixel( int x, int y, unsigned char grayscale )
{
    return WritePixel( x, y, grayscale, grayscale, grayscale );
}

void EdgeDetector::AllocateOutputImage()
{
    cout << "\tCopying image:" << bmp->GetFilepath() << " to:" << filename << endl;
    if( outbmp != NULL )
        delete outbmp;
    
    //fill pixel data with 0's (black)
    outbmp = new BMPImage( *bmp, filename, 0 );
}

void EdgeDetector::WriteBMP()
{
    cout << "\tWriting edge pixel data to the output BMP file: " << filename << endl;
    outbmp->Write();
}








