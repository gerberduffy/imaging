#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

#include <iostream>
#include <math.h>
#include <string.h>

using namespace cv;
using namespace std;

//The original image, and the image after the transform
Mat original, transformed;

void help()
{
	cout <<
	"\nA program using pyramid scaling, Canny, contours, contour simpification and\n"
	"memory storage (it's got it all folks) to find\n"
	"squares in a list of images pic1-6.png\n"
	"Returns sequence of squares detected on the image.\n"
	"the sequence is stored in the specified memory storage\n"
	"Call:\n"
	"./squares\n"
    "Using OpenCV version %s\n" << CV_VERSION << "\n" << endl;
}

void print_mat(Mat& src){
    int width = src.size().width;
    int height = src.size().height;

    int i, j;
    for (i=0; i < height; i++){
        for (j=0; j < width; j++){
            cout << (src.at<double>(i,j));
            cout << " ";
        }
        cout << "" << endl;
    }
}

/*
 * Return a blurred copy of the image
 */
Mat img_blurred(Mat& src){
    Mat blurred;
    cv::GaussianBlur(src, blurred, Size(5,5),0,0);
    //cv::blur(src, blurred, Size(20,20));
    return blurred;
}

Mat img_inv(Mat& src){
    Mat inversed = src.clone();
    return inversed.inv(cv::DECOMP_SVD);
}

/*
 * Return the transpose of the image
 */
Mat img_transposed(Mat& src){
    return src.t();
}

/*
 * Put in here whatever image transformations you want
 */
Mat transform(Mat& img, char command){
   cout << "Performing the transforms..." << endl;

   switch(command){
        //Transpose the image
       case 't': return img_transposed(img);
                 break;;

        //Apply a blur to the image
       case 'b': return img_blurred(img);
                 break;;
       case 'p': print_mat(img);
                 break;;
       
       case 'i': return img_inv(img);
                 break;;

        //Set the image back to the original
       case 'r': return original; 
                 break;;
       
        //Default: Leave the image alone
       default: return img; 
                break;;
    }
}

/*
 * Show the transformed image in the "transformed" window
 */
void update_transformed(){

    cout << "Showing the transform..." << endl;
    cv::imshow("transformed", transformed);
}
    

int main(int argc, char** argv)
{
    cout << "Showing image..." << endl;
    original = cv::imread("imgs/prince", CV_LOAD_IMAGE_COLOR);
    transformed = Mat(original);//= cv::imread("smile", CV_LOAD_IMAGE_COLOR);

    cout << "Image type = " << original.depth() << endl;
    
    cv::namedWindow("original");
    cv::namedWindow("transformed");
    //    cv::namedWindow("identity");

    cout << "Displaying prince image" << endl;
    cv::imshow("original", original);
    cout << "Img displayed" << endl;
    cv::imshow("transformed", transformed);

    //    cv::imshow("identity", ident);
    while (true){
        int key=cv::waitKey();
        if (key == 'q'){
            cv::destroyWindow("original");
            cv::destroyWindow("transformed");
            original.release();
            transformed.release();

            exit(0);
        } else{
            transformed = transform(transformed, key);
        }

        update_transformed();
    }
    
    cout << "Images displaying." << endl;
    return 0;
}
