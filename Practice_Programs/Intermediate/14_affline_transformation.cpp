#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>

int main() {

    cv::Mat img = cv::imread("D:/opencv-cpp/images/docs1.jpeg");
    if (img.empty()) {
        std::cerr << "Cannot load image\n"; return -1;
    }

    // source and destination points (float)
    std::vector<cv::Point2f> pts1{
        cv::Point2f(50.0f, 50.0f),
        cv::Point2f(200.0f, 50.0f),
        cv::Point2f(50.0f, 200.0f)
    };

    std::vector<cv::Point2f> pts2{
        cv::Point2f(10.0f, 70.0f),
        cv::Point2f(200.0f, 50.0f),
        cv::Point2f(100.0f, 250.0f)
    };

    // get affline transform matrix
    cv::Mat M = cv::getAffineTransform(pts1, pts2);

    // apply transform (warpAffline)
    cv::Mat dst;
    cv::warpAffine(img, dst, M, img.size());

    //show result (two windows)
    cv::namedWindow("Input", cv::WINDOW_AUTOSIZE);
    cv::imshow("Input", img);

    cv::namedWindow("Output", cv::WINDOW_AUTOSIZE);
    cv::imshow("Output", dst);

    //wait until a key is pressed
    cv::waitKey(0);

    return 0;
}
