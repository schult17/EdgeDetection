#ifndef __BASICEDGEDETECTOR_H_
#define __BASICEDGEDETECTOR_H_

#define THRESHOLD 120

#include "Filter.h"

class BasicEdgeDetector : public Filter
{
public:
    BasicEdgeDetector( BMPImage *bmpimage )
    : Filter( bmpimage ), one_direction_detector_called( false ){}
    
    BasicEdgeDetector( BMPImageData *bmp )
    : Filter( bmp ), one_direction_detector_called( false ){}
    
    virtual void ApplyFilter();
    
private:
    void FindEdges(bool horizontal);
    void HorizontalEdges();
    void VerticalEdges();
    bool one_direction_detector_called;
};

#endif

