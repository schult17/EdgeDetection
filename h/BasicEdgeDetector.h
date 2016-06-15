#ifndef __BASICEDGEDETECTOR_H_
#define __BASICEDGEDETECTOR_H_

#define THRESHOLD 120

#include "EdgeDetector.h"

class BasicEdgeDetector : public EdgeDetector
{
public:
    BasicEdgeDetector();
    BasicEdgeDetector( BMPImage *bmp );
    virtual void EdgeDetection();
    
private:
    void FindEdges(bool horizontal);
    void HorizontalEdges();
    void VerticalEdges();
    bool one_direction_detector_called;
};

#endif

