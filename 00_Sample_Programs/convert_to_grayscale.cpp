#include <opencv2/opencv.hpp>
using namespace cv;

int main() {
    Mat img = imread("D:/opencv-cpp/light.png");
    Mat gray;
    cvtColor(img, gray, COLOR_BGR2GRAY);

    imshow("Original", img);
    imshow("Gray", gray);
    waitKey(0);
    return 0;
}
