
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

    cv::Mat th_otsu;

    double otsu_thresh_val = cv::threshold( image, th_otsu, 0, 255, cv::THRESH_BINARY | cv::THRESH_OTSU );

    std::cout << "Otsu Threshold Value = " << otsu_thresh_val << std::endl;

    cv::imshow("Original", image);
    cv::imshow("Otsu Threshold", th_otsu);

    cv::waitKey(0);
    return 0;
}
