#include "string_art/string_art.hpp"

using namespace string_art;

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <thickness_mm>\n";
        return 1;
    }

    const float thickness_mm = static_cast<float>(std::atof(argv[1]));
    const float pixel_length = 1.0f;  // 1 mm per pixel

    cv::Mat canvas(40, 40, CV_8UC4, cv::Scalar(0, 0, 0, 255));  // black

    // three lines with different angles
    add_string(
        canvas, {5, 5}, {35, 10}, {{0, 0, 255, 255}, thickness_mm},
        pixel_length
    );  // red full
    add_string(
        canvas, {5, 20}, {35, 20}, {{0, 0, 255, 180}, thickness_mm},
        pixel_length
    );  // red semi
    add_string(
        canvas, {5, 35}, {35, 30}, {{0, 0, 255, 60}, thickness_mm},
        pixel_length
    );  // red dim

    cv::imshow("lines", canvas);
    cv::waitKey(0);
    return 0;
}
