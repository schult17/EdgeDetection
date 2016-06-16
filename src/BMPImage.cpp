#include "BMPImage.h"
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <cstddef>
#include <cmath>

//TODO -- support 8 bit grayscale as well as 24 bit RGB

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
    memcpy( bmpFileHeader, cpy.bmpFileHeader, FILE_HEADER_SIZE );
    pixelArrayOffset = cpy.pixelArrayOffset;
    memcpy( bmpInfoHeader, cpy.bmpInfoHeader, INFO_HEADER_SIZE );
    
    
    width = cpy.width;
    height = cpy.height;
    bitsPerPixel = cpy.bitsPerPixel;
    
    rowSize = cpy.rowSize;
    pixelArraySize = cpy.pixelArraySize;
    
    pixelData = new unsigned char[pixelArraySize];
    
    if( init_val == NULL )
        memcpy( pixelData, cpy.pixelData, pixelArraySize );
    else
        memset( pixelData, *init_val, pixelArraySize );
    
    this->filename = filename;
    
    //making copy of actual image
    ofstream copyfile( filename.c_str(), ios_base::out | ios_base::binary  );
    ifstream infile( cpy.filename.c_str(), ios_base::in | ios_base::binary  );
    
    if( !infile )
        cerr << "Couldn't open input file: " << cpy.filename << endl;
    
    if( !copyfile )
        cerr << "Couldn't open output file: " << filename << endl;
    
    char c;
    while(infile)
    {
        infile.read( &c, 1 );
        copyfile.write( &c, 1 );
    }
    
    type = cpy.type;
}

BMPImage::~BMPImage()
{
    delete pixelData;
    pixelData = NULL;
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

void BMPImage::Read()
{
    cout << "\tReading BMP file: " << filename << endl;
    ifstream infile( filename.c_str(), ios_base::in | ios_base::binary );
    
    if( !infile )
    {
        cerr << "\tUnable to open file: " << filename << endl;
        exit(-1);
    }
    
    //read from the file into this unsigned char
    char read = '\0';
    
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
        cerr << "\tSomething is probably wrong...BMPImage.cpp: " << __LINE__ << endl;
        //exit(-1);
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
    
    if( bitsPerPixel != 24 && bitsPerPixel != 8 )
    {
        cerr << "\t" << bitsPerPixel << " bits per pixel is not supported currently." << endl;
        exit(-1);
    }
    else
    {
        //8 bit grayscale or 24 bit RGB, figure it out
        switch( bitsPerPixel )
        {
            case 8:
                type = _8BIT_GRAY;
                break;
            case 24:
                type = _24BIT_RGB;
                break;
            default:
                type = UNKWN;
                break;
        }
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
    
    pixelData = new unsigned char[pixelArraySize];
    
    infile.seekg( pixelArrayOffset, ios::beg );
    
    for( int i = 0; i < pixelArraySize; i++ )
    {
        infile.read( &read, 1 );
        pixelData[i] = (unsigned char)read;
    }
    //------------------------//
    
    cout << "\tDone" << endl;
}

BMPPixel * BMPImage::getPixel( int x, int y )
{
    y = height - 1 - y;     //must flip Y
    
    if( x >= 0 && x <= width && y >= 0 && y <= height )
    {
        if( type == _24BIT_RGB )
        {
            int pixel_base = rowSize * y + RGB_PIXEL_WIDTH * x;
            
            unsigned char R, G, B;
            R = pixelData[pixel_base + 2];
            G = pixelData[pixel_base + 1];
            B = pixelData[pixel_base];
            
            return new RGBPixel24( R, G, B );
        }
        else        //8 bit grayscale
        {
            int pixel_base = rowSize * y + GRAY_PIXEL_WIDTH * x;
            unsigned char gray = pixelData[pixel_base];
            return new GrayPixel8( gray );
        }
    }
    else        //useful for edge detection, return black outside image
    {
        out_of_bounds_pixel_read = true;
        return ((type == _24BIT_RGB) ?
                static_cast<BMPPixel*>( new RGBPixel24(0x00, 0x00, 0x00) ) :
                static_cast<BMPPixel*>( new GrayPixel8(0x00) )
                );
    }
}

string BMPImage::GetFilename()
{
    size_t found = filename.find_last_of( '/' );
    if( found != string::npos )
        return filename.substr( found+1 );
    else
        return filename;
}

void BMPImage::setPixel( int x, int y, BMPPixel *pixel )
{
    y = height - 1 - y;         //flipping
    
    //editing data in pixelData array
    if( pixel->type == _24BIT_RGB )
    {
        RGBPixel24 *p = (RGBPixel24 *)pixel;
        int pixel_base = rowSize * y + RGB_PIXEL_WIDTH * x;
        pixelData[pixel_base + 2] = p->R;
        pixelData[pixel_base + 1] = p->G;
        pixelData[pixel_base] = p->B;
    }
    else
    {
        GrayPixel8 *p = (GrayPixel8 *)pixel;
        pixelData[rowSize * y + GRAY_PIXEL_WIDTH * x] = p->grayscale;
    }
}

void BMPImage::writePixel( int x, int y, std::fstream &file )
{
    BMPPixel *pixel = getPixel( x, y );
    
    y = height - 1 - y;         //flipping
    
    if( pixel->type == _24BIT_RGB )
    {
        RGBPixel24 *p = (RGBPixel24 *)pixel;
        int base_offset = pixelArrayOffset + rowSize * y + RGB_PIXEL_WIDTH * x;
        
        //write to file
        file.seekg( base_offset, ios::beg );
        file << p->B;
        file.seekg( base_offset + 1, ios::beg );
        file << p->G;
        file.seekg( base_offset + 2, ios::beg );
        file << p->R;
    }
    else            //8 bit grayscale
    {
        //TODO -- why is this red?
        GrayPixel8 *p = (GrayPixel8 *)pixel;
        file.seekg( pixelArrayOffset + rowSize * y + GRAY_PIXEL_WIDTH * x, ios::beg );
        file << p->grayscale;
    }
    
    //free allocated pixel for dynamic casting
    delete pixel;
    pixel = NULL;
}

void BMPImage::Write()
{
    fstream file( filename.c_str() );
    
    for( int x = 0; x < width; x++ )
        for( int y = 0; y < height; y++ )
            writePixel( x, y, file );
}


