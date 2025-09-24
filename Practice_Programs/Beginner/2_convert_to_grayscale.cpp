// Convert to Grayscale

#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>

int main() {
    std::string inputPath = "D:/opencv-cpp/images/light.png";
    std::string outputPath = "D:/opencv-cpp/images/gray_image.png";

    cv::Mat image = cv::imread(inputPath, cv::IMREAD_COLOR);

    if (image.empty()) {
        std::cerr << "Error: Image not found at path: " << inputPath << std::endl;
        return -1;
    }

    cv::Mat grayscale = cv::imread(inputPath, cv::IMREAD_GRAYSCALE);

    bool success = cv::imwrite(outputPath, grayscale);

    if (success) {
        std::cout << "GrayScale Image saved successfully as: " << outputPath << std::endl;
    } else {
        std::cerr << "Error: Failed to save the Grayscale image. Possible issues include invalid path or permissions." << std::endl;
        return -1;
    }

    cv::imshow("Original Image", image);
    cv::imshow("Grayscale Image", grayscale);
    cv::waitKey(0);
    cv::destroyAllWindows();

    return 0;
}