
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <vector>


int main()
{
    std::string image_path = "D:/opencv-cpp/images/light.png";
    cv::Mat image = cv::imread(image_path, cv::IMREAD_GRAYSCALE);

    if (image.empty()) {
        std::cerr << "Error: Image not found at path: " << image_path << std::endl;
        return -1;
    }

    double threshold_value = 127;
    double max_value = 255;

    cv::Mat th1, th2, th3, th4, th5;
    cv::threshold(image , th1, 127, 255, cv::THRESH_BINARY);
    cv::threshold(image , th2, 127, 255, cv::THRESH_BINARY_INV);
    cv::threshold(image , th3, 127, 255, cv::THRESH_TRUNC);
    cv::threshold(image , th4, 127, 255, cv::THRESH_TOZERO);
    cv::threshold(image , th5, 127, 255, cv::THRESH_TOZERO_INV);

    cv::imshow("Original", image);
    cv::imshow("Binary", th1);
    cv::imshow("Binary Inv", th2);
    cv::imshow("Trunc", th3);
    cv::imshow("ToZero", th4);
    cv::imshow("ToZero Inv", th5);

    cv::waitKey(0);
    return 0;
}
