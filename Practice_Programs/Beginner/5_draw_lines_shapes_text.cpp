#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>

int main() {
    cv::Mat canvas = cv::Mat::zeros(cv::Size(500, 500), CV_8UC3);

    circle(canvas, cv::Point(250, 250), 100, cv::Scalar(0, 0, 255), cv::FILLED);
    rectangle(canvas, cv::Point(50, 50), cv::Point(200, 200), cv::Scalar(0, 255, 0), 2);
    putText(canvas, "OpenCV", cv::Point(150, 400), cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(255, 255, 255), 2);

    std::string outputPath = "D:/opencv-cpp/images/canvas.png";

    bool success = imwrite(outputPath, canvas);

    if (success) {
        std::cout << "Canvas saved successfully as: " << outputPath << std::endl;
    } else {
        std::cerr << "Error: Failed to save the canvas. Possible issues include invalid path or permissions." << std::endl;
        return -1;
    }
    cv::imshow("Canvas", canvas);
    cv::waitKey(0);
    cv::destroyAllWindows();
    return 0;
}
