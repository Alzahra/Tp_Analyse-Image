#include "compute_histogram.h"

using namespace cv;
using namespace std;

/*contient les fonctions permettant
 - de calculer
 - d’afficher
 l’histogramme d’une image en niveaux de gris*/

//void Compute_Histogram::setImage(Mat prec)
//{
//    cout<<"setImage"<<endl;
//    image =prec;
//
//    cout<<"fin setImage"<<endl;
//
//}

Compute_Histogram::Compute_Histogram(Mat imagebase){
     image = imagebase;
}

void Compute_Histogram::CalculHist()
{
     /***HISTO IMAGE DE BASE****/
    
    int nbpixel = image.rows * image.cols;
    indmax =0;
 
    
    //Initialisation
    for (int i = 0; i <255; ++i){
        histogram[i] = 0;
    }
    
    // calculate the number of pixels for each intensity values
    for(int y = 0; y < image.rows; y++)
        for(int x = 0; x < image.cols; x++)
            histogram[(int)image.at<uchar>(y,x)]++;
    
    // find the maximum intensity element from histogram
    max = histogram[0];
    for(int i = 0; i < 255; i++)
        if(max < histogram[i]){
            max = histogram[i];
            indmax = i;
        }
    
    //Frequence
    for(int i = 0; i<255;i++)
        histd[i] = histogram[i]*100./(double)nbpixel;
    //cout<<"indmax"<<indmax<<"histd[indmax] = "<<histd[indmax]<<endl;
    
    /******HISTO IMAGE ETENDUE*****/
    
    //Pour l'expansion on cherche les bornes
    
    max = -1;
    int i = 255;
    while (max <0 && i>0){
        if(histogram[i])
            max = i;
        i--;
    }
    //cout<<"max"<<max<<endl;
    
    min = -1;
    i =0;
    while(min <0 && i<255){
        if(histogram[i])
            min = i;
        i++;
    }
    //cout<<"min"<<min<<endl;
    
    /* Calcul dans la classe image!expansion.cpp grâce aux bornes*/
    /* Affichage de l'image reajuste */
}

void Compute_Histogram::Affiche()
{
    //bins = intervals
    int width = 512; int height = 100;
    int bin_w = 2; //cvRound((double) hist_w/256);
    
    Mat histImage(height, width, CV_8UC1, Scalar(255));
    
    //Draw Histo de base
    for(int i = 0; i < 255; i++)
        line(histImage, Point(bin_w*i, height),
             Point(bin_w*i, height - histd[i]*100/histd[indmax]),
             Scalar(0));
    
    //Affichage de l'image
    namedWindow("Display window"); /* Create a window for display */
    imshow( "Display window", image );  /* Show our image inside it */
    
    // display histogram de base
    namedWindow("Intensity Histogram", CV_WINDOW_AUTOSIZE);
    imshow("Intensity Histogram", histImage);
    
 
}

double Compute_Histogram::getMax(){
    return max;
}

double Compute_Histogram::getMin(){
    return min;
}




