#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <vector>

using namespace cv;
using namespace std;

int main()
{
    string image_path1 = "D:/opencv-cpp/images/tesla.png";
    string image_path2 = "D:/opencv-cpp/images/light.png";

    Mat image1 = imread(image_path1, IMREAD_GRAYSCALE);
    resize(image1, image1, { 500,500 }, 0, 0, cv::INTER_NEAREST);

    Mat image2 = imread(image_path2, IMREAD_GRAYSCALE);
    resize(image2, image2, { 500,500 }, 0, 0, cv::INTER_NEAREST);

    MatND histogram;
    int histSize = 256;
    const int* channel_numbers = { 0 };
    float channel_range[] = { 0.0, 256.0 };
    const float* channel_ranges = channel_range;
    int number_bins = histSize;

    calcHist(&image1, 1, 0, Mat(), histogram, 1, &number_bins, &channel_ranges);

    int hist_w = 512, hist_h = 400;
    int bin_w = cvRound((double)hist_w / histSize);
    Mat histImage(hist_h, hist_w, CV_8UC3, Scalar(0, 0, 0));
    normalize(histogram, histogram, 0, histImage.rows, NORM_MINMAX, -1, Mat());

    for(int i = 1; i < histSize; i++){

    line(histImage, Point(bin_w * (i - 1), hist_h - cvRound(histogram.at<float>(i - 1))),
         Point(bin_w * (i), hist_h - cvRound(histogram.at<float>(i))),
         Scalar(255, 0, 0), 2, 8, 0);
    }

    MatND histogram2;

    calcHist(&image2, 1, 0, Mat(), histogram2, 1, &number_bins, &channel_ranges);

    Mat histImage2(hist_h, hist_w, CV_8UC3, Scalar(0, 0, 0));
    normalize(histogram2, histogram2, 0, histImage2.rows, NORM_MINMAX, -1, Mat());

    for (int i = 1; i < histSize; i++){

    line(histImage2, Point(bin_w * (i - 1), hist_h - cvRound(histogram2.at<float>(i - 1))),
         Point(bin_w * (i), hist_h - cvRound(histogram2.at<float>(i))),
         Scalar(255, 0, 0), 2, 8, 0);
    }

    double histMatchingCorrelation = compareHist(histogram, histogram2, HISTCMP_CORREL);
    double histMatchingChiSquare = compareHist(histogram, histogram2, HISTCMP_CHISQR);
    double histMatchingIntersection = compareHist(histogram, histogram2, HISTCMP_INTERSECT);
    double histMatchingBhattacharyya = compareHist(histogram, histogram2, HISTCMP_BHATTACHARYYA);

    cout << "Correlation: " << histMatchingCorrelation << endl;
    cout << "ChiSquare: " << histMatchingChiSquare<< endl;
    cout << "Intersection: " << histMatchingIntersection << endl;
    cout << "Bhattacharyya: " << histMatchingBhattacharyya << endl;

    imshow("Source image 1", image1);
    imshow("calcHist 1", histImage);
    imshow("Source image 2", image2);
    imshow("calcHist 2", histImage2);
    waitKey(0);

    return 0;
}