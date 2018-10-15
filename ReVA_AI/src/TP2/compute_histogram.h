//  compute_histogram.h

#ifndef compute_histogram_h
#define compute_histogram_h

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <iostream>
#include <string>

using namespace cv;

class Compute_Histogram{
    
    private :
    Mat image;
    
    int histogram[256];
    
    //Frequence
    double histd[256];
    int indmax;
    double max, min;
    
    public :
    Compute_Histogram(Mat);
    void CalculHist();
    void Affiche();
    
    double getMax();
    double getMin();
    
    //void setImage(Mat);
    
};


#endif /* compute_histogram_h */
