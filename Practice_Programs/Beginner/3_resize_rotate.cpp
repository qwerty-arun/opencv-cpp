// Resize and Rotate an image

#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>

int main() {
    std::string inputPath = "D:/opencv-cpp/images/light.png";
    std::string outputPath = "D:/opencv-cpp/images/resize_rotated_image.png";

    cv::Mat image = cv::imread(inputPath, cv::IMREAD_COLOR);

    if (image.empty()) {
        std::cerr << "Error: Image not found at path: " << inputPath << std::endl;
        return -1;
    }

    int new_width = 500;
    int new_height = 500;

    cv::Mat new_image;
    cv::resize(image, new_image, cv::Size(new_width, new_height));
    cv::rotate(new_image, new_image, cv::ROTATE_90_CLOCKWISE);
    cv::imshow("Original Image", image);
    cv::imshow("Resized and Rotated Image", new_image);
    cv::waitKey(0);
    cv::destroyAllWindows();

    bool success = cv::imwrite(outputPath, new_image);

    if (success) {
        std::cout << "Image saved successfully as: " << outputPath << std::endl;
    } else {
        std::cerr << "Error: Failed to save the image. Possible issues include invalid path or permissions." << std::endl;
        return -1;
    }
    return 0;
}