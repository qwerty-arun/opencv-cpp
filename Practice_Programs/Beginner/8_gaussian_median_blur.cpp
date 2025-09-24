// Gaussian Blur and Median Blur
#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>

int main() {
    std::string inputPath = "D:/opencv-cpp/images/light.png";
    std::string outputGaussianPath = "D:/opencv-cpp/images/gaussian_image.png";
    std::string outputMedianPath = "D:/opencv-cpp/images/median_image.png";

    cv::Mat image = cv::imread(inputPath, cv::IMREAD_COLOR);

    if (image.empty()) {
        std::cerr << "Error: Image not found at path: " << inputPath << std::endl;
        return -1;
    }

    cv::Mat gaussian, median;
    cv::GaussianBlur(image, gaussian, cv::Size(5, 5), 1.5);
    cv::medianBlur(image, median, 5);

    cv::imshow("Gaussian Blur", gaussian);
    cv::imshow("Median Blur", median);
    cv::waitKey(0);
    cv::destroyAllWindows();

    bool success1 = cv::imwrite(outputGaussianPath, image);

    if (success1) {
        std::cout << "Image saved successfully as: " << outputGaussianPath << std::endl;
    } else {
        std::cerr << "Error: Failed to save the image. Possible issues include invalid path or permissions." << std::endl;
        return -1;
    }

    bool success2 = cv::imwrite(outputMedianPath, image);

    if (success2) {
        std::cout << "Image saved successfully as: " << outputMedianPath << std::endl;
    } else {
        std::cerr << "Error: Failed to save the image. Possible issues include invalid path or permissions." << std::endl;
        return -1;
    }

    return 0;
}