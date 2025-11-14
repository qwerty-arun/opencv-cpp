#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>

int main()
{
    std::string image_path = "D:/opencv-cpp/images/light.png";
    cv::Mat image = cv::imread(image_path, cv::IMREAD_GRAYSCALE);

    cv::resize(image, image, cv::Size(500, 500));

    // MORPH_RECT, MORPH_ELLIPSE, MORPH_CROSS are the structuring elements
    cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));

    /*
    Morphological Gradient
        - Difference between dilation and erosion.
        - Highlights object boundaries
    */
    cv::Mat gradient;
    cv::morphologyEx(image, gradient, cv::MORPH_GRADIENT, kernel);

    /*
    Top Hat
        - Extracts small elements brighter than their surroundings.
        - TopHat = src - Opening
    */
    cv::Mat tophat;
    cv::morphologyEx(image, tophat, cv::MORPH_TOPHAT, kernel);

    /*
    Black Hat
        - Extracts dark regions on bright background.
        - BlackHat = Closing - src
    */

    cv::Mat blackhat;
    cv::morphologyEx(image, blackhat, cv::MORPH_BLACKHAT, kernel);

    cv::imshow("Original", image);
    cv::imshow("Gradient", gradient);
    cv::imshow("Top Hat", tophat);
    cv::imshow("Black Hat", blackhat);

    cv::waitKey(0);
    cv::destroyAllWindows();

    return 0;
}
