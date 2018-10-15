#include <stdio.h>
#include <iostream>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"



using namespace std;
using namespace cv;


//Image
Mat src, src2;

//Canny
Mat abs_dst, detected_edges;
Mat grad2;

/// Sobel et laplace
Mat src_gray, grad;
Mat grad_x, grad_y;
Mat abs_grad_x, abs_grad_y;

int scale = 0;
const int alpha_slider_max = 50;
int alpha_slider;

int delta = 0;
const int delta_slider_max = 255;
int delta_slider;

//highthreshold
const int amax_canny_max = 200;
int amax_canny;

//lowthreshold
const int alpha_canny_max = 100;
int alpha_canny;


//CalculContours
double contours_detecte=0;
double contours_ref = 0;
double contour_correct = 0;
double faux_positif = 0;
double faux_negatif = 0;

double performance = 0 ;
double tfp = 0 ;
double tfn = 0 ;

void calculbinary(Mat imgc){
    
    for(int y = 0; y < imgc.rows; y++){
        for(int x = 0; x < imgc.cols; x++){
            if(imgc.at<uchar>(y,x) < 127)
                imgc.at<uchar>(y,x) = 0;
            if(imgc.at<uchar>(y,x) >= 127)
                imgc.at<uchar>(y,x) = 255;
        }
    }
}

//255 c'est blanc, un contours est noir donc < 50 ?
int detec(Mat image, int seuil) {
    int contours = 0;
    for(int y = 0; y < image.rows; y++)
        for(int x = 0; x < image.cols; x++)
            if(image.at<uchar>(y,x) == seuil)
                contours++;
    return contours;
}

//si contours detecte ? est ce que contours detecter aussi sur src2
int correc(Mat imgcal){
    int intersection = 0;
    
    for(int y = 0; y < imgcal.rows; y++)
        for(int x = 0; x < imgcal.cols; x++)
            if(imgcal.at<uchar>(y,x) == 255 )
               if(src2.at<uchar>(y,x) == 0 )
                intersection++;
    return intersection;
}

void calcul(int val){
    
    contours_detecte=0;
    
    if(val == 1){
        
        //calculbinary(grad2);
        threshold(grad2,grad2, 100, 255, cv::THRESH_BINARY);
        
        contours_detecte = detec(grad2,255);
        contour_correct = correc(grad2);
        faux_positif = contours_detecte - contour_correct;
        faux_negatif = contours_ref - contour_correct;
        
        performance = contour_correct/(contour_correct+faux_negatif+faux_positif);
        tfp = faux_positif/(contour_correct+faux_negatif+faux_positif);
        tfn = faux_negatif/(contour_correct+faux_negatif+faux_positif);
        
        cout<< " Canny CD " << contours_detecte << " CC " << contour_correct << " FP "<< faux_positif << " FN " << faux_negatif << " P " << performance << " TFP " << tfp << " TFN " << tfn << endl;
        
    }
    if (val == 2){
        
        calculbinary(abs_dst);
        //threshold(abs_dst,abs_dst, 200, 255, cv::THRESH_BINARY);
        
        contours_detecte = detec(abs_dst,255);
        contour_correct = correc(abs_dst);
        faux_positif = contours_detecte - contour_correct;
        faux_negatif = contours_ref - contour_correct;
        
        performance = contour_correct/(contour_correct+faux_negatif+faux_positif);
        tfp = faux_positif/(contour_correct+faux_negatif+faux_positif);
        tfn = faux_negatif/(contour_correct+faux_negatif+faux_positif);
    
        cout<< " Laplace CD " << contours_detecte << " CC " << contour_correct << " FP "<< faux_positif << " FN " << faux_negatif << " P " << performance << " TFP " << tfp << " TFN " << tfn << endl;
    }
    
    if (val == 3){
        
        calculbinary(grad);
        //threshold(grad,grad, 120, 255, cv::THRESH_BINARY);
        
        contours_detecte = detec(grad,255);
        contour_correct = correc(grad);
        faux_positif = contours_detecte - contour_correct;
        faux_negatif = contours_ref - contour_correct;
        
        performance = contour_correct/(contour_correct+faux_negatif+faux_positif);
        tfp = faux_positif/(contour_correct+faux_negatif+faux_positif);
        tfn = faux_negatif/(contour_correct+faux_negatif+faux_positif);
       
        cout<< " Sobel CD " << contours_detecte << " CC " << contour_correct << " FP "<< faux_positif << " FN " << faux_negatif << " P " << performance << " TFP " << tfp << " TFN " << tfn << endl;
    }

}


//void Sobel(InputArray src, OutputArray dst, int ddepth, int dx, int dy, int ksize=3, double scale=1, double delta=0, int borderType=BORDER_DEFAULT )
//dx – order of the derivative x. & dy – order of the derivative y.
void sobel(){
    
    
    /// Gradient X
    //Scharr( src_gray, grad_x, ddepth, 1, 0, scale, delta, BORDER_DEFAULT );
    Sobel( src_gray, grad_x, CV_16S, 1, 0, 3, scale, delta, BORDER_DEFAULT );
    convertScaleAbs( grad_x, abs_grad_x );
    
    /// Gradient Y
    //Scharr( src_gray, grad_y, ddepth, 0, 1, scale, delta, BORDER_DEFAULT );
    Sobel( src_gray, grad_y, CV_16S, 0, 1, 3, scale, delta, BORDER_DEFAULT );
    convertScaleAbs( grad_y, abs_grad_y );
    
    /// Total Gradient (approximate)
    addWeighted( abs_grad_x, 0.5, abs_grad_y, 0.5, 0, grad );
    
    /*******/
    calcul(3);
    /******/
    
    imshow( "Sobel Demo", grad );
}

void laplace(){

    Laplacian( src_gray, grad, CV_16S, 3, scale, delta, BORDER_DEFAULT );
    convertScaleAbs( grad, abs_dst );
    
    /*************/
    calcul(2);
    /************/
    
    /// Show what you got
    imshow( "Laplace Demo", abs_dst );
}

void canny(){
 
    /// Reduce noise with a kernel 3x3
    GaussianBlur( src_gray, detected_edges, Size(3,3), 0, 0, BORDER_DEFAULT );
    //blur( src_gray, detected_edges, Size(3,3) );

    /// Canny detector
    Canny( detected_edges, detected_edges, alpha_canny, amax_canny_max, 3 );
    
    /// Using Canny's output as a mask, we display our result
    grad2 = Scalar::all(0);
    src.copyTo( grad2, detected_edges);
    
    /***********/
    calcul(1);
    /**********/
    
    imshow( "Canny Demo", grad2 );
}


void filtrecanny(int, void*){
    canny();
}

void filtre(int, void*){

    scale = (double)alpha_slider ;
    delta = (double)delta_slider;

    sobel();
    laplace();

}


int main( int argc, char** argv )
{
    /// Load an image
    src = imread(argv[1]);
    src2 = imread(argv[2]);
    
    int size = 0;
    ///Size
    for(int y = 0; y < src.rows; y++)
        for(int x = 0; x < src.cols; x++)
            size++;
    cout<<"Nb pixel totaux 1ere image : "<<size<<endl;
    
    size = 0;
    for(int y = 0; y < src2.rows; y++)
        for(int x = 0; x < src2.cols; x++)
            size++;

    cout<<"Nb pixel totaux image de ref : "<<size<<endl;
    
    if( !src.data )
    { return -1; }

//    ///void GaussianBlur(InputArray src, OutputArray dst, Size ksize, double sigmaX, double sigmaY=0, int borderType=BORDER_DEFAULT )
    //GaussianBlur( src, src, Size(3,3), 0, 0, BORDER_DEFAULT );

    /// Convert it to gray
    cvtColor( src, src_gray, CV_BGR2GRAY );

    /// Sobel et Laplace
    namedWindow( "Sobel Demo", CV_WINDOW_AUTOSIZE );
    moveWindow("Sobel Demo", 10, 200);
    
    namedWindow( "Laplace Demo", CV_WINDOW_AUTOSIZE );
    moveWindow("Laplace Demo", 550, 200);
    
    namedWindow( "Image Ref", CV_WINDOW_AUTOSIZE );
    moveWindow("Image Ref", 1100, 200);
    imshow( "Image Ref", src2 );
    
    namedWindow( "Trackbar Sobel & Laplace", CV_WINDOW_NORMAL );
    moveWindow("Trackbar Sobel & Laplace", 300, 150);
    
    char TrackbarName[50];
    sprintf( TrackbarName, "Alpha x %d", alpha_slider_max);
    createTrackbar( TrackbarName, "Trackbar Sobel & Laplace", &alpha_slider, alpha_slider_max, filtre );

    char TrackbarName1[50];
    sprintf( TrackbarName1, "Delta x %d", delta_slider_max);
    createTrackbar( TrackbarName1, "Trackbar Sobel & Laplace", &delta_slider, delta_slider_max, filtre );
    
    contours_ref = 0;
    contours_ref = detec(src2,0);
    cout<< "Contours de Reference " << contours_ref <<endl;
    sobel();
    laplace();
    canny();
    
    /// Canny
    namedWindow( "Canny Demo", CV_WINDOW_AUTOSIZE );
    moveWindow("Canny Demo", 1100, 200);
    
    namedWindow( "TrackbarCanny1", CV_WINDOW_NORMAL );
    moveWindow("TrackbarCanny1", 1300, 150);

    char TrackbarName2[50];
    sprintf( TrackbarName2, "LowThreshold x %d", alpha_canny_max );
    createTrackbar( TrackbarName2, "TrackbarCanny1", &alpha_canny, alpha_canny_max, filtrecanny );


    char TrackbarName3[50];
    sprintf( TrackbarName3, "HighThreshold x %d", amax_canny_max );
    createTrackbar( TrackbarName3, "TrackbarCanny1", &amax_canny, amax_canny_max, filtrecanny );

    
    waitKey(0);
    return 0;
}


