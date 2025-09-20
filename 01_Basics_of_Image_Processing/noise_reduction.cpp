#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

const int max_value_H = 360 / 2;
const int max_value = 255;

int main(){
    string image_path1 = "D:/opencv-cpp/images/black_hole.jpg";
    string image_path2 = "D:/opencv-cpp/images/light.png";
    string image_path3 = "D:/opencv-cpp/images/tesla.png";

    Mat image1 = imread(image_path2, IMREAD_COLOR);
    resize(image1, image1, {500, 500});

    if(image1.empty()){
        cout << "Could not read the image" << endl;
        return -1;
    }

    vector<int> lower_bound = {170, 80, 50};

    int low_H = lower_bound[0], low_S = lower_bound[1], low_V = lower_bound[2];
    int high_H = max_value_H, high_S = max_value, high_V = max_value;

    Mat hsvImg, imgThreshold;

    //Convert from BGR to HSV colorspace
    cvtColor(image1, hsvImg, COLOR_BGR2HSV);
    //Detect the object based on HSV Range Values
    inRange(hsvImg, Scalar(low_H, low_S, low_V), Scalar(high_H, high_S, high_V), imgThreshold);

    Mat medianBlurImg, gaussianBlurImg;
    medianBlur(image1, medianBlurImg, 9);
    GaussianBlur(image1, gaussianBlurImg, Size(1, 1), 9, 9);

    imshow("Original Image", image1);
    imshow("Median Blurred Image", medianBlurImg);
    imshow("Gaussian Blurred Image", gaussianBlurImg);

    // imshow("Original Image", image1);
    // imshow("HSV Image", hsvImg);
    // imshow("Threshold Image", imgThreshold);

    int k = waitKey(0);

    if(k == 'q'){
        cv::destroyAllWindows();
    }
    return 0;
}