#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

class Threshold
{
private:
    std::string image_path;
    cv::Mat image;

public:
    Threshold(std::string path) : image_path(path),
                                  image(cv::imread(image_path, cv::IMREAD_GRAYSCALE))
    {
    }

    void resize()
    {
        cv::resize(this->image, this->image, cv::Size(500, 500));
    }

    void simple_threshold()
    {
        double threshold_value = 127;
        double max_value = 255;

        cv::Mat th1, th2, th3, th4, th5;
        cv::threshold(image, th1, 127, 255, cv::THRESH_BINARY);
        cv::threshold(image, th2, 127, 255, cv::THRESH_BINARY_INV);
        cv::threshold(image, th3, 127, 255, cv::THRESH_TRUNC);
        cv::threshold(image, th4, 127, 255, cv::THRESH_TOZERO);
        cv::threshold(image, th5, 127, 255, cv::THRESH_TOZERO_INV);

        cv::imshow("Original", image);
        cv::imshow("Binary", th1);
        cv::imshow("Binary Inv", th2);
        cv::imshow("Trunc", th3);
        cv::imshow("ToZero", th4);
        cv::imshow("ToZero Inv", th5);

        cv::waitKey(0);
        cv::destroyAllWindows();
    }

    void adaptive_threshold()
    {
        cv::Mat th_mean, th_gauss;

        cv::adaptiveThreshold(image, th_mean, 255, cv::ADAPTIVE_THRESH_MEAN_C, cv::THRESH_BINARY, 11, 2);

        cv::adaptiveThreshold(image, th_gauss, 255, cv::ADAPTIVE_THRESH_GAUSSIAN_C, cv::THRESH_BINARY, 11, 2);

        cv::imshow("Original", image);
        cv::imshow("Adaptive Mean", th_mean);
        cv::imshow("Adaptive Gaussian", th_gauss);

        cv::waitKey(0);
        cv::destroyAllWindows();
    }

    void otsu_threshold()
    {
        cv::Mat th_otsu;

        double otsu_thresh_val = cv::threshold(image, th_otsu, 0, 255, cv::THRESH_BINARY | cv::THRESH_OTSU);

        std::cout << "Otsu Threshold Value = " << otsu_thresh_val << std::endl;

        cv::imshow("Original", image);
        cv::imshow("Otsu Threshold", th_otsu);

        cv::waitKey(0);
        cv::destroyAllWindows();
    }
};

int main()
{
    std::string image_path = "D:/opencv-cpp/images/light.png";
    Threshold th("D:/opencv-cpp/images/light.png");
    th.resize();
    th.simple_threshold();
    th.adaptive_threshold();
    th.otsu_threshold();
    return 0;
}