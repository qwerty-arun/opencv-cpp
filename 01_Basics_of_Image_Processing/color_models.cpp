#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <string>

using namespace std;

int main(){
    string image_path1 = "D:/opencv-cpp/light.png";
    string image_path2 = "D:/opencv-cpp/light.png";

    cv::Mat image1 = cv::imread(image_path1, cv::IMREAD_COLOR);
    cv::Mat image2 = cv::imread(image_path2, cv::IMREAD_COLOR);

    if(image1.empty() || image2.empty()){
        cout << "Could not read the image" << endl;
        return 1;
    }

    cv::rotate(image2, image2, cv::ROTATE_90_COUNTERCLOCKWISE);
    cv::resize(image2, image2, cv::Size(500, 500));

    // cv::Vec3b colorModification = {231, 54, 154};

    for (int i = 0; i < image2.rows; i++){
        for (int j = 0; j < image2.cols; j++){
            // astro2.at<cv::Vec3b>(i, j) = colorModification;

            cv::Vec3b bgrPixel = image2.at<cv::Vec3b>(i, j);
            // cout << "bgr: " << bgrPixel << endl;
            // Grayscale = (R + G + B) / 3

            unsigned char grayScale = (bgrPixel[2] + bgrPixel[1] + bgrPixel[0]) / 3;

            image2.at<cv::Vec3b>(i, j) = {grayScale, grayScale, grayScale};

            cv::Vec3b grayPixel = image2.at<cv::Vec3b>(i, j);

            // cout << "gray: " << grayPixel << endl;
        }
    }
    
    cv::imshow("First", image1);
    cv::imshow("Second", image2);
    cv::waitKey(0);  // waits indefinitely until a key is pressed
    cv::destroyAllWindows();  // optional, closes all windows after key press

    /*
        int k = cv::waitKey(0);
        if(k == 's'){
        cv::imwrite("new_image.png", image2);
        }
    */
    return 0;
}