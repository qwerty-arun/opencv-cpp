#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>

int main()
{
    std::string image_path = "D:/opencv-cpp/images/light.png";
    cv::Mat image = cv::imread(image_path, cv::IMREAD_GRAYSCALE);

    cv::resize(image, image, cv::Size(500, 500));

    /*
    Erosion:
        - Removes pixels on object boundaries.
        - Shrinks white regions (foreground).
        - Good for removing small white noise.
    */
    cv::Mat eroded;
    cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));
    cv::erode(image, eroded, kernel);

    /*
    Dilation:
        - Adds pixels to object boundaries.
        - Expands white regions.
        - Useful for filling small holes.
    */
    cv::Mat dilated;
    cv::dilate(image, dilated, kernel);

    /*
    Opening = Erosion -> Dilation
        - Removes small white noise.
        - Smooths object contours.
    */
    cv::Mat opened;
    cv::morphologyEx(image, opened, cv::MORPH_OPEN, kernel);

    /*
    Closing = Erosion -> Dilation
        - Fills small black holes inside objects.
        - Connects nearby white regions.
    */
    cv::Mat closed;
    cv::morphologyEx(image, closed, cv::MORPH_CLOSE, kernel);

    cv::imshow("Original", image);
    cv::imshow("Erosion", eroded);
    cv::imshow("Dilation", dilated);
    cv::imshow("Opened", opened);
    cv::imshow("Closed", closed);

    cv::waitKey(0);
    cv::destroyAllWindows();

    return 0;
}
