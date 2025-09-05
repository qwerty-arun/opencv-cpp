#include <stdio.h>
#include <opencv2/opencv.hpp>

using namespace cv;

int main(){
    Mat image;
    image = imread("D:/opencv-cpp/light.png");
    if(!image.data){
        printf("No image data\n");
        return -1;
    }
    namedWindow("Display Image", WINDOW_AUTOSIZE);
    imshow("Display Image", image);
    waitKey(0);
    return 0;
}