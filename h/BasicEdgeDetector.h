#ifndef __BASICEDGEDETECTOR_H_
#define __BASICEDGEDETECTOR_H_

#define THRESHOLD 120

#include "Filter.h"

class BasicEdgeDetector : public Filter
{
public:
    BasicEdgeDetector( BMPImage *bmpimage );
    BasicEdgeDetector( BMPImageData *bmp );
    virtual void ApplyFilter();
    
private:
    void FindEdges(bool horizontal);
    void HorizontalEdges();
    void VerticalEdges();
    bool one_direction_detector_called;
};

#endif

