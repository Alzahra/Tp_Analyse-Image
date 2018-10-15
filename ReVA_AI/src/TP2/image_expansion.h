//  image_expansion.h

#ifndef image_expansion_h
#define image_expansion_h

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <iostream>
#include <string>

using namespace cv;

class Image_Expansion{
    
    private :
    Mat imageexp;
   
    //bornes
    double max;
    double min;
    
    int indmax2;
    int histogram2[256];
    
    //Frequence
    double histd2[256];

    void Modifhist();
    
    public :
    Image_Expansion(Mat, double, double);
    //void setImage(Mat);
    void Affiche();
    
};

#endif /* image_expansion_h */
