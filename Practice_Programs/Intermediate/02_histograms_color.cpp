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

    Mat image1 = imread(image_path1, IMREAD_COLOR);
    resize(image1, image1, { 500,500 }, 0, 0, cv::INTER_NEAREST);

    Mat image2 = imread(image_path2, IMREAD_COLOR);
    resize(image2, image2, { 500,500 }, 0, 0, cv::INTER_NEAREST);

    /// --- Split channels (B, G, R) ---
    vector<Mat> bgr_planes1, bgr_planes2;
    split(image1, bgr_planes1);
    split(image2, bgr_planes2);

    /// --- Histogram parameters ---
    int histSize = 256;
    float range[] = { 0, 256 };
    const float* histRange = { range };
    bool uniform = true, accumulate = false;

    Mat hist1_b, hist1_g, hist1_r;
    Mat hist2_b, hist2_g, hist2_r;

    /// --- Calculate per-channel histograms ---
    calcHist(&bgr_planes1[0], 1, 0, Mat(), hist1_b, 1, &histSize, &histRange, uniform, accumulate);
    calcHist(&bgr_planes1[1], 1, 0, Mat(), hist1_g, 1, &histSize, &histRange, uniform, accumulate);
    calcHist(&bgr_planes1[2], 1, 0, Mat(), hist1_r, 1, &histSize, &histRange, uniform, accumulate);

    calcHist(&bgr_planes2[0], 1, 0, Mat(), hist2_b, 1, &histSize, &histRange, uniform, accumulate);
    calcHist(&bgr_planes2[1], 1, 0, Mat(), hist2_g, 1, &histSize, &histRange, uniform, accumulate);
    calcHist(&bgr_planes2[2], 1, 0, Mat(), hist2_r, 1, &histSize, &histRange, uniform, accumulate);

    /// --- Normalize ---
    int hist_w = 512, hist_h = 400;
    int bin_w = cvRound((double) hist_w / histSize);

    normalize(hist1_b, hist1_b, 0, hist_h, NORM_MINMAX);
    normalize(hist1_g, hist1_g, 0, hist_h, NORM_MINMAX);
    normalize(hist1_r, hist1_r, 0, hist_h, NORM_MINMAX);

    normalize(hist2_b, hist2_b, 0, hist_h, NORM_MINMAX);
    normalize(hist2_g, hist2_g, 0, hist_h, NORM_MINMAX);
    normalize(hist2_r, hist2_r, 0, hist_h, NORM_MINMAX);

    /// --- Draw histograms on same image ---
    Mat histImage1(hist_h, hist_w, CV_8UC3, Scalar(0,0,0));
    Mat histImage2(hist_h, hist_w, CV_8UC3, Scalar(0,0,0));

    for( int i = 1; i < histSize; i++ )
    {
        line(histImage1, Point(bin_w*(i-1), hist_h - cvRound(hist1_b.at<float>(i-1))),
                          Point(bin_w*(i), hist_h - cvRound(hist1_b.at<float>(i))),
                          Scalar(255, 0, 0), 2, 8, 0);
        line(histImage1, Point(bin_w*(i-1), hist_h - cvRound(hist1_g.at<float>(i-1))),
                          Point(bin_w*(i), hist_h - cvRound(hist1_g.at<float>(i))),
                          Scalar(0, 255, 0), 2, 8, 0);
        line(histImage1, Point(bin_w*(i-1), hist_h - cvRound(hist1_r.at<float>(i-1))),
                          Point(bin_w*(i), hist_h - cvRound(hist1_r.at<float>(i))),
                          Scalar(0, 0, 255), 2, 8, 0);

        line(histImage2, Point(bin_w*(i-1), hist_h - cvRound(hist2_b.at<float>(i-1))),
                          Point(bin_w*(i), hist_h - cvRound(hist2_b.at<float>(i))),
                          Scalar(255, 0, 0), 2, 8, 0);
        line(histImage2, Point(bin_w*(i-1), hist_h - cvRound(hist2_g.at<float>(i-1))),
                          Point(bin_w*(i), hist_h - cvRound(hist2_g.at<float>(i))),
                          Scalar(0, 255, 0), 2, 8, 0);
        line(histImage2, Point(bin_w*(i-1), hist_h - cvRound(hist2_r.at<float>(i-1))),
                          Point(bin_w*(i), hist_h - cvRound(hist2_r.at<float>(i))),
                          Scalar(0, 0, 255), 2, 8, 0);
    }

    /// --- Compare histograms (on all channels combined) ---
    double corr = compareHist(hist1_b, hist2_b, HISTCMP_CORREL) +
                  compareHist(hist1_g, hist2_g, HISTCMP_CORREL) +
                  compareHist(hist1_r, hist2_r, HISTCMP_CORREL);

    cout << "Correlation (sum of BGR): " << corr << endl;

    /// --- Show results ---
    imshow("Image 1", image1);
    imshow("Histogram 1 (BGR)", histImage1);

    imshow("Image 2", image2);
    imshow("Histogram 2 (BGR)", histImage2);

    waitKey(0);
    return 0;
}
