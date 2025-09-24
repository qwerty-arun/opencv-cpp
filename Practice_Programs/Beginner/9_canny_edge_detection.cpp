// Apply Canny Edge Detection

#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>

int main() {
    std::string inputPath = "D:/opencv-cpp/images/light.png";
    std::string outputPath = "D:/opencv-cpp/images/edges_image.png";

    cv::Mat image = cv::imread(inputPath, cv::IMREAD_COLOR);

    if (image.empty()) {
        std::cerr << "Error: Image not found at path: " << inputPath << std::endl;
        return -1;
    }

    cv::Mat edges;
    cv::Canny(image, edges, 50, 150);

    cv::imshow("Original Image", image);
    cv::imshow("Edge Detection", edges);
    cv::waitKey(0);
    cv::destroyAllWindows();

    bool success = cv::imwrite(outputPath, edges);

    if (success) {
        std::cout << "Image saved successfully as: " << outputPath << std::endl;
    } else {
        std::cerr << "Error: Failed to save the image. Possible issues include invalid path or permissions." << std::endl;
        return -1;
    }

    return 0;
}