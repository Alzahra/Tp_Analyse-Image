#include "image_expansion.h"

using namespace cv;
using namespace std;

/*réalise la
 - modification du contraste de l’image comme
 demandée dans ce TP*/

Image_Expansion::Image_Expansion(Mat image, double max, double min)
{
    imageexp = image;
    this->max = max;
    this->min = min;
}

void Image_Expansion::Modifhist()
{
    int nbpixel = imageexp.rows * imageexp.cols;
    indmax2=0;
    
    //Initialisation
    for (int i = 0; i <255; ++i){
        histogram2[i] = 0;
    }
    
    for(int y = 0; y < imageexp.rows; y++)
        for(int x = 0; x < imageexp.cols; x++)
            imageexp.at<uchar>(y,x) = (255.*(imageexp.at<uchar>(y,x)-min))/(max - min);
    
    // calculate the number of pixels for each intensity values
    for(int y = 0; y < imageexp.rows; y++)
        for(int x = 0; x < imageexp.cols; x++)
            histogram2[(int)imageexp.at<uchar>(y,x)]++;
    
    //Find the maximum intensity element from histogram
    max = 0;
    for(int i = 0; i <255; i++)
        if(max < histogram2[i]){
            max = histogram2[i];
            indmax2 = i;
        }
    
    //Frequence
    for(int i = 0; i<255;i++)
        histd2[i] = histogram2[i]*100./(double)nbpixel;
    
    //cout<<"indmax2"<<indmax2<<"histd2[indmax2] = "<<histd2[indmax2]<<endl;
}

void Image_Expansion::Affiche()
{
    Modifhist();
    
    //bins = intervals
    int width = 512; int height = 100;
    int bin_w = 2; //cvRound((double) hist_w/256);
    
    Mat histImage2(height, width, CV_8UC1, Scalar(255));
    
    //Draw Histo etendu
    for(int i = 0; i < 255; i++)
        line(histImage2, Point(bin_w*i, height),
             Point(bin_w*i, height - histd2[i]*100/histd2[indmax2]),
             Scalar(0));
    
    /*Image modifiee*/
    namedWindow("Display window1"); /* Create a window for display */
    imshow( "Display window1", imageexp );  /* Show our image inside it */
    
    // display histogram etendu
    namedWindow("Intensity Histogram1", CV_WINDOW_AUTOSIZE);
    imshow("Intensity Histogram1", histImage2);
    
}

//void Image_Expansion::setImage(Mat prec)
//{
//    cout<<"SetImage"<<endl;
////    for(int y = 0; y < prec.rows; y++)
////        for(int x = 0; x < prec.cols; x++)
////            imageexp.at<uchar>(y,x) = prec.at<uchar>(y,x);
//
//    imageexp = prec;
//
//}

