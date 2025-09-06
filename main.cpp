#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>

int main(){
    cv::Mat img = cv::imread("path");

    if(img.empty()){
        std::cout << "Error loading image, image not found!\n";
        return -1;
    }
    
    cv::Mat gray;
    cv::cvtColor(img, gray, cv::COLOR_BGR2GRAY);
    cv::imshow("Original", img);
    cv::imshow("Gray", gray);
    cv::waitKey(0);
    return 0;
}