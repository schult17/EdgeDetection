#include "Filter.h"
#include <iostream>

using namespace std;

Filter::Filter( BMPImage *inimage )
{
    indata = inimage->getPixelData();
    outdata = new BMPImageData( *indata );
}

Filter::Filter( BMPImageData *indata )
: indata( indata )
{
    outdata = new BMPImageData( *indata );
}

Filter::~Filter()
{
    delete outdata;
}

void Filter::ApplyFilter()
{
    cerr << "FATAL: You attempted to use the 'Filter' base class to apply a filtering algorithm" << endl;
    cerr << "\tYou should use one of the derived classes to filter data" << endl;
    exit(-1);
}

void Filter::SwapInputOutputData()
{
    BMPImageData *tmp = indata;
    indata = outdata;
    outdata = tmp;
}

void Filter::ClearOutputData( int clear_val )
{
    outdata->ClearData( clear_val );
}

void Filter::SwapAndClear( int clear_val )
{
    SwapInputOutputData();
    ClearOutputData( clear_val );
}

bool Filter::WriteWhitePixel( int x, int y )
{
    return WritePixel( x, y, 0xFF, 0xFF, 0xFF );
}

bool Filter::WriteBlackPixel( int x, int y )
{
    return WritePixel( x, y, 0x00, 0x00, 0x00 );
}

bool Filter::WritePixel( int x, int y, unsigned char R, unsigned G, unsigned B )
{
    if( x < 0 || x > outdata->getWidth() || y < 0 || y > outdata->getHeight() )
    {
        return false;
    }
    else
    {
        outdata->setPixel( x, y, BMPPixel(R, G, B) );
        return true;
    }
}

bool Filter::WritePixel( int x, int y, unsigned char grayscale )
{
    return WritePixel( x, y, grayscale, grayscale, grayscale );
}

