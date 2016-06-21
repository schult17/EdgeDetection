#include "BMPImage.h"
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <cstddef>
#include <cmath>

using namespace std;

bool BMPImage::out_of_bounds_pixel_read = false;

BMPImage::BMPImage( string filename )
: filename( filename )
{
    Read();
}

BMPImage::BMPImage( const BMPImage &cpy, string filename )
: filename( filename )
{
    OnCopy( cpy );
    pixelData = new BMPImageData( *(cpy.pixelData) );
}

BMPImage::BMPImage( const BMPImage &cpy, std::string filename, BMPImageData * cpyData )
: filename( filename )
{
    if( cpyData == NULL )
    {
        cerr << __FILE__ << ":" << __LINE__ << "\tcpyData is NULL" << endl;
        exit(-1);
    }
    
    OnCopy( cpy );
    pixelData = new BMPImageData( *cpyData );
}

void BMPImage::OnCopy( const BMPImage &cpy )
{
    //Copy the header data (same type of image)
    memcpy( bmpFileHeader, cpy.bmpFileHeader, FILE_HEADER_SIZE );
    pixelArrayOffset = cpy.pixelArrayOffset;
    memcpy( bmpInfoHeader, cpy.bmpInfoHeader, INFO_HEADER_SIZE );
    
    paddingSize = cpy.paddingSize;
    
    if( paddingSize != 0 )
    {
        padding = new unsigned char[paddingSize];
        memcpy( padding, cpy.padding, paddingSize );
    }
    else
    {
        padding = NULL;
    }
}

BMPImage::~BMPImage()
{
    if( pixelData ) delete pixelData;
    if( padding )   delete padding;
}

void BMPImage::swapPixelData( BMPImageData *newData )
{
    *pixelData = *newData;
}

void BMPImage::Read()
{
    cout << "\tReading BMP file: " << filename << endl;
    ifstream infile( filename.c_str(), ios_base::in | ios_base::binary );
    
    if( !infile )
    {
        cerr << "\tUnable to open file: " << filename << endl;
        exit(-1);
    }
    
    //BMP variables
    int height;
    int width;
    int bitsPerPixel;
    
    int rowSize;
    int pixelArraySize;
    unsigned char *pixel_data;
     
    //read from the file into this unsigned char
    char read = '\0';
    
    //------------------------//
    //read in the file header
    for( int i = 0; i < FILE_HEADER_SIZE; i++ )
    {
        infile.read( &read, 1 );
        bmpFileHeader[i] = (unsigned char)read;
    }
    
    if( bmpFileHeader[0] != 'B' || bmpFileHeader[1] != 'M' )
    {
        cerr << "\tInfo header may be incorrect, it should begin with 'BM'" << endl;
    }
    
    pixelArrayOffset = *( (unsigned int *)(bmpFileHeader + 10) );
    
    if( bmpFileHeader[11] != 0 || bmpFileHeader[12] != 0 || bmpFileHeader[13] != 0 )
    {
        cerr << "\tSomething is probably wrong with the image...BMPImage.cpp: " << __LINE__ << endl;
        exit(-1);
    }
    //------------------------//
    
    //reading in the info header
    for( int i = 0; i < INFO_HEADER_SIZE; i++ )
    {
        infile.read( &read, 1 );
        bmpInfoHeader[i] = (unsigned char)read;
    }
    
    //get width and height of file
    width = *( (int*)(bmpInfoHeader+4) );
    height = *( (int*)(bmpInfoHeader+8) );
    
    cout << "\tWidth: " << width << " Height: " << height << endl;
    
    bitsPerPixel = bmpInfoHeader[INFO_BITS_PER_PIXEL_OFFSET];
    
    if( bitsPerPixel != 24 )
    {
        cerr << "\t" << bitsPerPixel << " bits per pixel is not supported currently." << endl;
        exit(-1);
    }
    
    if( bmpInfoHeader[INFO_COMPRESSION_OFFSET] != 0 )
    {
        cerr << "\tCompressed BMP files are not supported..." << endl;
        exit(-1);
    }
    //------------------------//
    
    //Calculating and reading pixel data
    rowSize = int( floor( (bitsPerPixel * width + 31.)/32 ) ) * 4;   //row size includes padding
    pixelArraySize = rowSize * abs(height);
    
    pixel_data = new unsigned char[pixelArraySize];
    
    //Read in the useless padding
    padding = NULL;
    paddingSize = (int)pixelArrayOffset - infile.tellg();
    
    if( paddingSize != 0 )
    {
        padding = new unsigned char[paddingSize];
        
        for( int i = 0; i < paddingSize; i++ )
        {
            infile.read( &read, 1 );
            padding[i] = (unsigned char)read;
        }
    }
    
    infile.seekg( pixelArrayOffset, ios::beg );
    
    for( int i = 0; i < pixelArraySize; i++ )
    {
        infile.read( &read, 1 );
        pixel_data[i] = (unsigned char)read;
    }
    //------------------------//
    
    //-----set BMP data in BMPImageData-----//
    //pixelData.setData( height, width, bitsPerPixel, rowSize, pixelArraySize, pixel_data );
    pixelData = new BMPImageData( height, width, bitsPerPixel, rowSize, pixelArraySize, pixel_data );
    //--------------------------------------//
    
    cout << "\tDone" << endl;
}

string BMPImage::GetFilename()
{
    size_t found = filename.find_last_of( '/' );
    
    if( found != string::npos )
        return filename.substr( found+1 );
    else
        return filename;
}

void BMPImage::Write()
{
    ofstream file( filename.c_str() );
    
    if( !file )
    {
        cerr << "Couldn't open Edge detection output file: " << filename << endl;
    }
    else
    {
        WriteHeaders( file );
        
        int width = pixelData->getWidth();
        int height = pixelData->getHeight();
        
        for( int x = 0; x < width; x++ )
            for( int y = 0; y < height; y++ )
                WritePixel( x, y, file );
    }
}

void BMPImage::WriteHeaders( ofstream &file )
{
    for( int i = 0; i < FILE_HEADER_SIZE; i++ )
        file << bmpFileHeader[i];
    
    for( int i = 0; i < INFO_HEADER_SIZE; i++ )
        file << bmpInfoHeader[i];
    
    for( int i = 0; i < paddingSize; i++ )
        file << padding[i];
}

void BMPImage::WritePixel( int x, int y, ofstream &file )
{
    BMPPixel pixel = pixelData->getPixel( x, y );
    
    y = pixelData->getHeight() - 1 - y;         //flipping
    
    int base_offset = pixelArrayOffset + pixelData->getRowSize() * y + RGB_PIXEL_WIDTH * x;
    
    //write to file, seekp, not seekg (writing past eof)
    file.seekp( base_offset, ios::beg );
    file << pixel.B;
    file.seekp( base_offset + 1, ios::beg );
    file << pixel.G;
    file.seekp( base_offset + 2, ios::beg );
    file << pixel.R;
    
}
