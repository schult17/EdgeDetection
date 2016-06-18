#include "BMPImage.h"
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <cstddef>
#include <cmath>

using namespace std;

bool BMPImage::out_of_bounds_pixel_read = false;

BMPImage::BMPImage( string filename ) : filename( filename )
{
    Read();
}

BMPImage::BMPImage( const BMPImage &cpy )
{
    cerr << "FATAL: The copy constructor of the BMPImage is not availible!\n\t"
            "The constructor: BMPImage( const BMPImage &cpy, string filename ) will not only copy the"
    "object, but also make a copy of the BMP image. You must use this, or pass the BMPImage by reference" << endl;
    
    exit(-1);
}

BMPImage::BMPImage( const BMPImage &cpy, string filename )
{
    onCopy( cpy, filename, NULL );
}

BMPImage::BMPImage( const BMPImage &cpy, string filename, int init_val )
{
    onCopy( cpy, filename, &init_val );
}

void BMPImage::onCopy( const BMPImage &cpy, string filename, int *init_val )
{
    //Copy the header data (same type of image)
    memcpy( bmpFileHeader, cpy.bmpFileHeader, FILE_HEADER_SIZE );
    pixelArrayOffset = cpy.pixelArrayOffset;
    memcpy( bmpInfoHeader, cpy.bmpInfoHeader, INFO_HEADER_SIZE );
    
    //Use BMPImageData's copy constructor with the init_val pointer
    delete pixelData;
    pixelData = new BMPImageData( *(cpy.pixelData), *init_val );
    
    //making copy of actual image
    ofstream copyfile( filename.c_str(), ios_base::out | ios_base::binary  );
    ifstream infile( cpy.filename.c_str(), ios_base::in | ios_base::binary  );
    
    if( !infile )
        cerr << "Couldn't open input file: " << cpy.filename << endl;
    
    if( !copyfile )
        cerr << "Couldn't open output file: " << filename << endl;
    
    //use read and write, << and >> may skip spaces (big headache)
    char c;
    while(infile)
    {
        infile.read( &c, 1 );
        copyfile.write( &c, 1 );
    }
    
    //This got deleted, don't let this get deleted...
    this->filename = filename;
}

BMPImage::~BMPImage()
{
    delete pixelData;
}

//Use this to delete the file AND the object.
//If the file is gone, the object is useless.s
void BMPImage::Remove()
{
    //remove the file
    int OK = remove( filename.c_str() );
    
    if( !OK )
    {
        cerr << "Error when trying to delete file: " << filename << endl;
        cerr << "Continuing to delete object..." << endl;
    }
    
    delete this;
}

BMPImageData BMPImage::getPixelData()
{
    if( pixelData == NULL )
    {
        cerr << "FATAL: trying to call getPixelData() on a BMPImage that does not have a BMPImageData object allocated" << endl;
        exit(-1);
    }
    else
    {
        return *pixelData;
    }
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

void BMPImage::writePixel( int x, int y, std::fstream &file )
{
    BMPPixel pixel = pixelData->getPixel( x, y );
    
    y = pixelData->getHeight() - 1 - y;         //flipping
    
    int base_offset = pixelArrayOffset + pixelData->getRowSize() * y + RGB_PIXEL_WIDTH * x;
    
    //write to file
    file.seekg( base_offset, ios::beg );
    file << pixel.B;
    file.seekg( base_offset + 1, ios::beg );
    file << pixel.G;
    file.seekg( base_offset + 2, ios::beg );
    file << pixel.R;
    
}

void BMPImage::Write()
{
    fstream file( filename.c_str() );
    
    if( !file )
    {
        cerr << "Couldn't open Edge detection output file: " << filename << endl;
    }
    else
    {
        int width = pixelData->getWidth();
        int height = pixelData->getHeight();
        
        for( int x = 0; x < width; x++ )
            for( int y = 0; y < height; y++ )
                writePixel( x, y, file );
    }
}


