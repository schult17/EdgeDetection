#ifndef __SOBELEDGEDETECTOR_H_
#define __SOBELEDGEDETECTOR_H_

#include "EdgeDetector.h"

class SobelEdgeDetector : public EdgeDetector
{
public:
    SobelEdgeDetector();
    SobelEdgeDetector( BMPImage *bmp );
    virtual void EdgeDetection();
};

#endif
