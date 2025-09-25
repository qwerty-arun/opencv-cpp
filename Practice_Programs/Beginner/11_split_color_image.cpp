#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main(){
    string image_path1 = "D:/opencv-cpp/images/light.png";

    Mat image1 = imread(image_path1, IMREAD_COLOR);
    cv::resize(image1, image1, cv::Size(400, 400));

    vector<cv::Mat> bgr_planes;
    split(image1, bgr_planes);

    if(image1.empty()){
        cout << "Could not read the image" << endl;
        return -1;
    }

    imshow("Original Image", image1);
    imshow("Blue Channel", bgr_planes[0]);
    imshow("Green Channel", bgr_planes[1]);
    imshow("Red Channel", bgr_planes[2]);

    int k = waitKey(0);

    if(k == 'q'){
        cv::destroyAllWindows();
    }
    return 0;
}