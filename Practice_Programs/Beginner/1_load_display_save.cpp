// Load, Display and Save an Image

#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>

int main() {
    std::string inputPath = "D:/opencv-cpp/images/light.png";
    std::string outputPath = "D:/opencv-cpp/images/new_image.png";

    cv::Mat image = cv::imread(inputPath, cv::IMREAD_COLOR);

    // 1. Check if the image was read successfully.
    if (image.empty()) {
        std::cerr << "Error: Image not found at path: " << inputPath << std::endl;
        return -1;
    }

    // Display the image to confirm it was read.
    cv::imshow("Display Window", image);
    cv::waitKey(0);
    cv::destroyAllWindows();

    // 2. Attempt to save the image and check the return value.
    bool success = cv::imwrite(outputPath, image);

    if (success) {
        std::cout << "Image saved successfully as: " << outputPath << std::endl;
    } else {
        std::cerr << "Error: Failed to save the image. Possible issues include invalid path or permissions." << std::endl;
        return -1;
    }

    return 0;
}