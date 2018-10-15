//  main.cpp

#include <stdio.h>
#include <iostream>
#include "compute_histogram.h"
#include "image_expansion.h"

using namespace std;
using namespace cv;

int main( int argc, char **argv ) {
        
    if ( argc != 2 ) {
        printf( "Usage: display_image ImageToLoadAndDisplay\n" );
        return -1;
    }
    
    Mat image = cv::imread(argv[1],CV_LOAD_IMAGE_GRAYSCALE); /* Read the file */
    
    if ( !image.data ) { /* Check for invalid input */
        printf("Could not open or find the image\n") ;
        return -1;
    }
    
    /*Affichage et Calcul des Histogrammes*/
    
    //cout<<"Compute"<<endl;
    Compute_Histogram c(image);
   
    //cout<<"CalculHist"<<endl;
    c.CalculHist();
    //cout<<"Affiche de c"<<endl;
    c.Affiche();
    
    //cout<<"Image Expansion"<<endl;
    Image_Expansion e(image, c.getMax(), c.getMin());
    
    //cout<<"Affiche de e"<<endl;
    e.Affiche();
    
    waitKey(0);  /* Wait for a keystroke in the window */
    return 0;

}
