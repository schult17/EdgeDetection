#ifndef __BMPPIXEL_H_
#define __BMPPIXEL_H_

class BMPPixel
{
public:
    BMPPixel();
    BMPPixel( unsigned char R, unsigned char G, unsigned char B );
    BMPPixel( unsigned char gray );
    
    unsigned int toGrayScale();
    bool isNull() { return Null; }
    
    unsigned char R;
    unsigned char G;
    unsigned char B;
    
private:
    bool Null;
};

#endif
