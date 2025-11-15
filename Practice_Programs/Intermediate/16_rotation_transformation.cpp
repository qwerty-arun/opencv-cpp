#include <opencv2/opencv.hpp>
#include <iostream>

int main()
{
    // Read image in grayscale
    cv::Mat img = cv::imread("D:/opencv-cpp/images/light.png", cv::IMREAD_GRAYSCALE);
    cv::resize(img, img, cv::Size(500, 500));
    if (img.empty()) {
        std::cerr << "Error: file could not be read. Check the path.\n";
        return -1;
    }

    int rows = img.rows;
    int cols = img.cols;

    // Rotation center (same as Python: (cols-1)/2, (rows-1)/2)
    cv::Point2f center((cols - 1) / 2.0f, (rows - 1) / 2.0f);

    // Get rotation matrix: angle = 90 degrees, scale = 1
    cv::Mat M = cv::getRotationMatrix2D(center, 90, 1.0);

    // Apply warpAffine with same output size
    cv::Mat dst;
    cv::warpAffine(img, dst, M, img.size());

    // Show images
    cv::imshow("Input", img);
    cv::imshow("Rotated", dst);
    cv::waitKey(0);

    return 0;
}
