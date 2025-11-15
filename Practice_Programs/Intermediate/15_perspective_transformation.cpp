// perspective.cpp
#include <opencv2/opencv.hpp>
#include <iostream>

int main()
{
    // load image
    cv::Mat img = cv::imread("D:/opencv-cpp/images/docs1.jpeg");
    if (img.empty()) {
        std::cerr << "Error: file could not be read. Check path or use std::filesystem::exists().\n";
        return -1;
    }

    // source points (4 corners in the source image)
    std::vector<cv::Point2f> pts1 {
        cv::Point2f(56.0f, 65.0f),
        cv::Point2f(368.0f, 52.0f),
        cv::Point2f(28.0f, 387.0f),
        cv::Point2f(389.0f, 390.0f)
    };

    // destination points (rectangle 300x300)
    std::vector<cv::Point2f> pts2 {
        cv::Point2f(0.0f, 0.0f),
        cv::Point2f(300.0f, 0.0f),
        cv::Point2f(0.0f, 300.0f),
        cv::Point2f(300.0f, 300.0f)
    };

    // get perspective transform matrix
    cv::Mat M = cv::getPerspectiveTransform(pts1, pts2);

    // apply warpPerspective
    cv::Mat dst;
    cv::warpPerspective(img, dst, M, img.size());

    // display input and output
    cv::namedWindow("Input", cv::WINDOW_AUTOSIZE);
    cv::imshow("Input", img);

    cv::namedWindow("Output", cv::WINDOW_AUTOSIZE);
    cv::imshow("Output", dst);

    // optionally save
    // cv::imwrite("sudoku_warped.png", dst);

    cv::waitKey(0);
    return 0;
}
