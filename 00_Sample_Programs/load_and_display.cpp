#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;

int main() {
    Mat img = imread("D:/opencv-cpp/light.png", IMREAD_COLOR);
    if (img.empty()) {
        std::cout << "Image not found!\n";
        return -1;
    }
    imshow("Display Window", img);
    waitKey(0);
    return 0;
}
