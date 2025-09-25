#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main(){
    string image_path = "D:/opencv-cpp/images/light.png";

    Mat image = imread(image_path, IMREAD_COLOR);
    cv::resize(image, image, cv::Size(400, 400));

    Mat horz, vert, both;
    cv::flip(image, horz, 1);
    cv::flip(image, vert, 0);
    cv::flip(image, both, -1);


    if(image.empty()){
        cout << "Could not read the image" << endl;
        return -1;
    }

    imshow("Original Image", image);
    imshow("Horizontal Flipped", horz);
    imshow("Vertical Flipped", vert);
    imshow("Both Flipped", both);
    waitKey(0);
    destroyAllWindows();
    return 0;
}