#include <opencv2/opencv.hpp>
#include <iostream>

int main()
{
    // Read image in grayscale
    cv::Mat img = cv::imread("D:/opencv-cpp/images/light.png", cv::IMREAD_GRAYSCALE);
    if (img.empty()) {
        std::cerr << "Error: file could not be read. Check the path.\n";
        return -1;
    }

    cv::resize(img, img, cv::Size(500, 500));

    int rows = img.rows;
    int cols = img.cols;

    // Translation matrix (same as Python: shift x by 100, y by 50)
    cv::Mat M = (cv::Mat_<float>(2, 3) << 
                  1, 0, 100,
                  0, 1, 50);

    // Apply affine transform
    cv::Mat dst;
    cv::warpAffine(img, dst, M, img.size());

    // Display result
    cv::imshow("Translated Image", dst);
    cv::waitKey(0);
    cv::destroyAllWindows();

    return 0;
}
