#include <opencv2/opencv.hpp>
#include <iostream>

int main() {
    // Create a 500x500 grayscale (single-channel) image, initialized to black
    cv::Mat canvas = cv::Mat::zeros(cv::Size(10, 10), CV_8UC1);

    // Draw a white filled circle at the center
    cv::circle(canvas, cv::Point(5, 5), 2, cv::Scalar(255), cv::FILLED);

    // Print the entire image matrix
    std::cout << "Image Matrix (20x20):\n";
    for (int y = 0; y < canvas.rows; y++) {
        for (int x = 0; x < canvas.cols; x++) {
            uchar pixel = canvas.at<uchar>(y, x);
            std::cout << (int)pixel << "\t";  // print as integer
        }
        std::cout << std::endl;
    }

    // Show the image
    // cv::imshow("Grayscale Image", canvas);
    cv::waitKey(0);
    cv::destroyAllWindows();

    return 0;
}
