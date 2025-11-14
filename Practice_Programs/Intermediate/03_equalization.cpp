#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <vector>

using namespace cv;
using namespace std;

int main()
{
    string image_path1 = "D:/opencv-cpp/images/house_dark.webp";

    Mat image1 = imread(image_path1, IMREAD_COLOR);
    resize(image1, image1, { 500,500 }, 0, 0, cv::INTER_NEAREST);

    Mat histEqualized;
    equalizeHist(image1, histEqualized);

    imshow("Source Image", image1);
    imshow("Equalized Image", histEqualized);
    waitKey(0);
    return 0;
}
