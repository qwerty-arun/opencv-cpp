
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <vector>


int main()
{
    std::string image_path = "D:/opencv-cpp/images/light.png";
    cv::Mat image = cv::imread(image_path, cv::IMREAD_GRAYSCALE);

    cv::resize(image, image, cv::Size(400, 400));

    if (image.empty()) {
        std::cerr << "Error: Image not found at path: " << image_path << std::endl;
        return -1;
    }

    cv::Mat th_mean, th_gauss;

    cv::adaptiveThreshold(image, th_mean, 255, cv::ADAPTIVE_THRESH_MEAN_C, cv::THRESH_BINARY, 11, 2);

    cv::adaptiveThreshold(image, th_gauss, 255, cv::ADAPTIVE_THRESH_GAUSSIAN_C, cv::THRESH_BINARY, 11, 2);

    cv::imshow("Original", image);
    cv::imshow("Adaptive Mean", th_mean);
    cv::imshow("Adaptive Gaussian", th_gauss);

    cv::waitKey(0);
    return 0;
}
