#include <opencv2/opencv.hpp>
using namespace cv;

int main() {
    Mat canvas = Mat::zeros(Size(500, 500), CV_8UC3);

    circle(canvas, Point(250, 250), 100, Scalar(0, 0, 255), FILLED);
    rectangle(canvas, Point(50, 50), Point(200, 200), Scalar(0, 255, 0), 2);
    putText(canvas, "OpenCV", Point(150, 400), FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 255, 255), 2);

    imshow("Canvas", canvas);
    waitKey(0);
    return 0;
}
