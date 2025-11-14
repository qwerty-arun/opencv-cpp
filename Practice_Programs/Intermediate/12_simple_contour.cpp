#include <opencv2/opencv.hpp>
using namespace cv;

int main() {
    Mat src = imread("D:/opencv-cpp/images/buildings.jpg");
    Mat gray, thresh;

    cvtColor(src, gray, COLOR_BGR2GRAY);
    threshold(gray, thresh, 120, 255, THRESH_BINARY);

    std::vector<std::vector<Point>> contours;
    std::vector<Vec4i> hierarchy;

    findContours(thresh, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

    Mat output = src.clone();
    drawContours(output, contours, -1, Scalar(0, 0, 255), 2);

    imshow("Original", src);
    imshow("Contours", output);
    waitKey();
    return 0;
}
