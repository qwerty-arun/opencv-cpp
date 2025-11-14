#include <opencv2/opencv.hpp>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include <map>

class Threshold {
public:
    // ctor throws if image can't be loaded
    Threshold(const std::string &path, bool load_as_gray = true) {
        image = load_as_gray ? cv::imread(path, cv::IMREAD_GRAYSCALE)
                             : cv::imread(path, cv::IMREAD_COLOR);
        if (image.empty()) {
            throw std::runtime_error("Failed to load image: " + path);
        }
    }

    // allow explicit resize; returns *this for chaining
    Threshold &resize(const cv::Size &sz) {
        cv::resize(image, image, sz);
        return *this;
    }

    // optional preprocessing: blur before Otsu/adaptive
    Threshold &gaussian_blur(int ksize = 5) {
        if (ksize % 2 == 0) ++ksize; // ensure odd
        cv::GaussianBlur(image, image, cv::Size(ksize, ksize), 0);
        return *this;
    }

    // simple threshold variants; returns map of name->mat (processing separated from display)
    std::map<std::string, cv::Mat> simple_threshold(double thresh = 127.0, double max_val = 255.0) const {
        std::map<std::string, cv::Mat> out;
        out["Binary"] = cv::Mat();
        out["Binary Inv"] = cv::Mat();
        out["Trunc"] = cv::Mat();
        out["ToZero"] = cv::Mat();
        out["ToZero Inv"] = cv::Mat();

        cv::threshold(image, out["Binary"], thresh, max_val, cv::THRESH_BINARY);
        cv::threshold(image, out["Binary Inv"], thresh, max_val, cv::THRESH_BINARY_INV);
        cv::threshold(image, out["Trunc"], thresh, max_val, cv::THRESH_TRUNC);
        cv::threshold(image, out["ToZero"], thresh, max_val, cv::THRESH_TOZERO);
        cv::threshold(image, out["ToZero Inv"], thresh, max_val, cv::THRESH_TOZERO_INV);

        return out;
    }

    // adaptive thresholding with parameters
    std::map<std::string, cv::Mat> adaptive_threshold(int block_size = 11, double C = 2.0) const {
        if (block_size % 2 == 0) ++block_size; // must be odd
        std::map<std::string, cv::Mat> out;
        out["Adaptive Mean"] = cv::Mat();
        out["Adaptive Gaussian"] = cv::Mat();

        cv::adaptiveThreshold(image, out["Adaptive Mean"], 255,
                              cv::ADAPTIVE_THRESH_MEAN_C, cv::THRESH_BINARY,
                              block_size, C);

        cv::adaptiveThreshold(image, out["Adaptive Gaussian"], 255,
                              cv::ADAPTIVE_THRESH_GAUSSIAN_C, cv::THRESH_BINARY,
                              block_size, C);

        return out;
    }

    // Otsu thresholding, optionally blur first (recommended)
    std::pair<double, cv::Mat> otsu_threshold(bool blur_first = true, int blur_ksize = 5) const {
        cv::Mat src = image;
        if (blur_first) {
            int k = blur_ksize % 2 == 0 ? blur_ksize + 1 : blur_ksize;
            cv::GaussianBlur(src, src, cv::Size(k, k), 0);
        }
        cv::Mat out;
        double val = cv::threshold(src, out, 0, 255, cv::THRESH_BINARY | cv::THRESH_OTSU);
        return {val, out};
    }

    // helper to show multiple images in a single window as a grid (resizes tiles to same size)
    static void show_grid(const std::string &win_name,
                          const std::vector<std::pair<std::string, cv::Mat>> &images,
                          int cols = 2, int tile_w = 300, int tile_h = 300,
                          int wait_ms = 0) {
        if (images.empty()) return;

        int rows = (int)std::ceil(images.size() / static_cast<double>(cols));
        std::vector<cv::Mat> tiles;
        for (auto &p : images) {
            cv::Mat tile;
            if (p.second.channels() == 1) cv::cvtColor(p.second, tile, cv::COLOR_GRAY2BGR);
            else tile = p.second.clone();

            cv::resize(tile, tile, cv::Size(tile_w, tile_h));
            // put label text
            cv::putText(tile, p.first, cv::Point(8, 20),
                        cv::FONT_HERSHEY_SIMPLEX, 0.6, cv::Scalar(255, 255, 255), 1);
            tiles.push_back(tile);
        }

        // build rows by horizontally concatenating tiles
        std::vector<cv::Mat> row_mats;
        for (int r = 0; r < rows; ++r) {
            std::vector<cv::Mat> row_tiles;
            for (int c = 0; c < cols; ++c) {
                int idx = r * cols + c;
                if (idx < (int)tiles.size()) row_tiles.push_back(tiles[idx]);
                else row_tiles.push_back(cv::Mat::zeros(cv::Size(tile_w, tile_h), tiles[0].type()));
            }
            cv::Mat row;
            cv::hconcat(row_tiles, row);
            row_mats.push_back(row);
        }

        cv::Mat grid;
        cv::vconcat(row_mats, grid);

        cv::namedWindow(win_name, cv::WINDOW_AUTOSIZE);
        cv::imshow(win_name, grid);
        cv::waitKey(wait_ms);
        // do not destroy here if caller wants to keep window; caller can call destroyAllWindows()
    }

    // returns original (const ref)
    const cv::Mat &get_original() const { return image; }

private:
    cv::Mat image;
};

// ------- Example main -------
int main() {
    try {
        Threshold th("D:/opencv-cpp/images/light.png");
        th.resize(cv::Size(500, 500));

        // simple thresholds
        auto simple = th.simple_threshold(127.0, 255.0);
        std::vector<std::pair<std::string, cv::Mat>> to_show;
        to_show.emplace_back("Original", th.get_original());
        for (auto &p : simple) to_show.emplace_back(p.first, p.second);

        Threshold::show_grid("Simple Thresholds", to_show, 3, 250, 250);

        // adaptive
        auto adapt = th.adaptive_threshold(11, 2.0);
        std::vector<std::pair<std::string, cv::Mat>> adapt_show;
        adapt_show.emplace_back("Original", th.get_original());
        for (auto &p : adapt) adapt_show.emplace_back(p.first, p.second);

        Threshold::show_grid("Adaptive Thresholds", adapt_show, 2, 350, 350);

        // Otsu
        auto [otsu_val, otsu_img] = th.otsu_threshold(true, 5);
        std::cout << "Otsu value: " << otsu_val << '\n';
        Threshold::show_grid("Otsu", {{"Original", th.get_original()}, {"Otsu", otsu_img}}, 2, 400, 400);

        // Pause until user closes
        cv::waitKey(0);
        cv::destroyAllWindows();
    } catch (const std::exception &ex) {
        std::cerr << "Error: " << ex.what() << '\n';
        return 1;
    }
    return 0;
}
