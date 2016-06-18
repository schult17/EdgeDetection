#ifndef __EDGEDETECTOR_H_
#define __EDGEDETECTOR_H_

#include "BMPImage.h"

class EdgeDetector
{
	public:
    EdgeDetector();
	EdgeDetector( BMPImage *bmp );
    ~EdgeDetector();
    
	void SetOutputFilePath( std::string filename );
    BMPImage* SetBMPimage( BMPImage *bmp );
    void DetectEdges();

	protected:
    
    //Note: You cannot call this directly, it must be implemented
    //      by a deriving class.
    virtual void EdgeDetection();
    
    //Writing to output BMP
    bool WriteWhitePixel( int x, int y );
    bool WriteBlackPixel( int x, int y );
    bool WritePixel( int x, int y, unsigned char R, unsigned G, unsigned B );
    bool WritePixel( int x, int y, unsigned char grayscale );
    
    void AllocateOutputImage();
    void MakeOutputDir();
    
    void WriteBMP();
    
	std::string filename;
    BMPImage *bmp;
    BMPImage *outbmp;
};

#endif
