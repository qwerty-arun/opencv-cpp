#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;

int main() {
    VideoCapture cap(0);
    if (!cap.isOpened()) {
        std::cout << "Cannot open camera\n";
        return -1;
    }

    Mat frame;
    while (true) {
        cap >> frame;
        if (frame.empty()) break;

        imshow("Webcam", frame);

        if (waitKey(10) == 27) break; // ESC key to exit
    }
    return 0;
}
