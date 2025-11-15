#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
using namespace cv;
using namespace std;

// (Include orderPoints() from above here)
// Order points: {tl, tr, br, bl}
vector<Point2f> orderPoints(const vector<Point2f>& pts) {
    vector<Point2f> out(4);
    // compute sum and diff
    vector<float> s(4), d(4);
    for (int i = 0; i < 4; ++i) {
        s[i] = pts[i].x + pts[i].y;      // tl has smallest sum, br largest
        d[i] = pts[i].x - pts[i].y;      // tr has smallest diff, bl largest
    }
    // top-left: min sum
    out[0] = pts[min_element(s.begin(), s.end()) - s.begin()];
    // bottom-right: max sum
    out[2] = pts[max_element(s.begin(), s.end()) - s.begin()];
    // top-right: min diff
    out[1] = pts[min_element(d.begin(), d.end()) - d.begin()];
    // bottom-left: max diff
    out[3] = pts[max_element(d.begin(), d.end()) - d.begin()];
    return out;
}

int main() {

    Mat img = imread("D:/opencv-cpp/images/docs1.jpeg");
    if (img.empty()) {
        cerr << "Cannot load image\n"; return -1;
    }

    // Example source points (in image coordinates) - replace with detected points
    vector<Point2f> srcPts = {
        Point2f(320, 120),  // approx top-left
        Point2f(900, 140),  // top-right
        Point2f(920, 700),  // bottom-right
        Point2f(300, 720)   // bottom-left
    };

    // Ensure consistent ordering
    srcPts = orderPoints(srcPts);

    // Destination size (A4-like rectangle) — width x height in pixels
    const float A4_W = 595;   // example: 595x842 at 72 DPI (or choose any)
    const float A4_H = 842;
    vector<Point2f> dstPts = {
        Point2f(0.0f, 0.0f),        // tl
        Point2f(A4_W - 1.0f, 0.0f), // tr
        Point2f(A4_W - 1.0f, A4_H - 1.0f), // br
        Point2f(0.0f, A4_H - 1.0f)  // bl
    };

    // Compute homography (4-point)
    Mat H = getPerspectiveTransform(srcPts, dstPts);

    // Apply warp
    Mat warped;
    warpPerspective(img, warped, H, Size((int)A4_W, (int)A4_H),
                    INTER_LINEAR, BORDER_CONSTANT);

    imshow("Input", img);
    imshow("Warped (top-down)", warped);
    waitKey(0);

    imwrite("unwarped.png", warped);
    return 0;
}
