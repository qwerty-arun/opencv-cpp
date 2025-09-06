#include <opencv2/opencv.hpp>
using namespace cv;

int main() {
    Mat img = imread("D:/opencv-cpp/light.png");
    Mat resized, rotated;

    resize(img, resized, Size(300, 300));
    rotate(img, rotated, ROTATE_90_CLOCKWISE);

    imshow("Resized", resized);
    imshow("Rotated", rotated);
    waitKey(0);
    return 0;
}
