#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <iostream>
#include <string>

using namespace cv;
using namespace std;

cv::Mat image;
Scalar* lclic;
int lignec = -1;

//Noir et blanc

void CallBackFunc(int event, int x, int y, int flags, void* userdata)
{
    float blue,green,red;
    if  ( event == EVENT_LBUTTONDOWN )
    {
        cout << "Left button of the mouse is clicked - position (" << x << ", " << y << ")" << endl;
        
        //recopie de la ligne si cliqué
        if(lignec>=0){
            for(int i = 0; i < image.cols; i++){
                image.at<Scalar>(lignec, i) = lclic[i];
            }
        }
        lignec = y;

        //Mémorisation de la ligne
        for(int i = 0; i < image.cols; i++){
            lclic[i] = image.at<Scalar>(y, i);
        }
        //Creation de l'image pour la courbe
        Mat courbe(256, image.cols, CV_8UC1, Scalar(255, 255, 255));
        for(int i=0;i<image.cols;i++){
            line(courbe, Point(i,256 - (int)image.at<uchar>(y, i)), Point(i+1,256 - (int)image.at<uchar>(y, i+1)), Scalar(0,0,0));
        }
        //Ligne clic couleur jaune
        for(int i=0;i<image.cols;i++){
            image.at<uchar>(y,i)= 100;
        }
       
        imshow( "Display window", image );  /* Show our image inside it */
        
        namedWindow("Courbe window");
        imshow( "Courbe window", courbe );
    }
}

int main( int argc, char **argv ) {

    if ( argc != 2 ) {
       printf( "Usage: display_image ImageToLoadAndDisplay\n" );
       return -1;
    }

    image = cv::imread(argv[1],CV_LOAD_IMAGE_GRAYSCALE); /* Read the file */

    lclic = new Scalar[image.cols](); //largeur de la ligne cliqué
    
    if ( !image.data ) { /* Check for invalid input */
        printf("Could not open or find the image\n") ;
        return -1;
    }
    
    cv::namedWindow("Display window"); /* Create a window for display */
    cv::setMouseCallback("Display window", CallBackFunc, NULL);
    cv::imshow( "Display window", image );  /* Show our image inside it */

    cv::waitKey(0);  /* Wait for a keystroke in the window */
    return 0;
}

