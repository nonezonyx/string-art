#include "string_art/string_art.hpp"
#include <cmath>
#include <istream>
#include <map>
#include <opencv2/core/types.hpp>
#include <ostream>

using namespace string_art;

namespace string_art {
namespace {
std::ostream &operator<<(std::ostream &os, const cv::Scalar &color) {
    os << "RGBA(" << color[2] << ", " << color[1] << ", ";
    return os << color[0] << ", " << color[3] << ")";
}

std::istream &operator>>(std::istream &is, cv::Scalar &color) {
    static const std::map<char, int> color_map = {
        {'R', 2}, {'G', 1}, {'B', 0}, {'A', 3}
    };
    char color_pos[4];
    is >> color_pos[0] >> color_pos[1] >> color_pos[2] >> color_pos[3];
    char c;
    is >> c;
    if (c != '(') {
        is.setstate(std::ios_base::failbit);
        return is;
    }
    for (int i = 0; i < 4; ++i) {
        if (color_map.find(color_pos[i]) == color_map.end()) {
            is.setstate(std::ios_base::failbit);
            return is;
        }
        is >> color[color_map.at(color_pos[i])];
        is >> c;
        if (c != (i == 3 ? ')' : ',')) {
            is.setstate(std::ios_base::failbit);
            return is;
        }
    }
    return is;
}

bool consume(std::istream &is, const std::string &str) {
    is >> std::ws;
    for (const char c : str) {
        if (is.get() != c) {
            is.setstate(std::ios_base::failbit);
            return false;
        }
    }
    return true;
}
}  // namespace
}  // namespace string_art

bool String::operator==(const String &other) const {
    return color == other.color &&
           abs(thickness - other.thickness) < THICKNESS_EPSILON;
}

std::ostream &string_art::operator<<(std::ostream &os, const String &string) {
    return os << "String(" << string.color << ", " << string.thickness << ")";
}

std::istream &string_art::operator>>(std::istream &is, String &string) {
    if (!consume(is, "String(")) {
        return is;
    }
    is >> string.color;
    if (!consume(is, ",")) {
        return is;
    }
    is >> string.thickness;
    if (!consume(is, ")")) {
        return is;
    }
    return is;
}

bool Metadata::operator==(const Metadata &other) const {
    return background_color == other.background_color &&
           canvas_width == other.canvas_width &&
           canvas_height == other.canvas_height &&
           pixel_length == other.pixel_length && palette == other.palette &&
           positions == other.positions;
}

std::ostream &
string_art::operator<<(std::ostream &os, const Metadata &metadata) {
    return os;
}

std::istream &string_art::operator>>(std::istream &is, Metadata &metadata) {
    return is;
}

void string_art::add_string(
    cv::Mat &image,
    const cv::Point2d &start,
    const cv::Point2d &end,
    const String &string,
    float pixel_length
) {
    assert(image.type() == CV_8UC4 && "Image must have an alpha channel");
    const float thickness = string.thickness / pixel_length;
    int thickness_rounded = std::ceil(thickness);

    int margin = thickness_rounded + 2;
    int min_x =
        std::max(0, std::min(cvRound(start.x), cvRound(end.x)) - margin);
    int min_y =
        std::max(0, std::min(cvRound(start.y), cvRound(end.y)) - margin);
    int max_x = std::min(
        image.cols - 1, std::max(cvRound(start.x), cvRound(end.x)) + margin
    );
    int max_y = std::min(
        image.rows - 1, std::max(cvRound(start.y), cvRound(end.y)) + margin
    );

    if (min_x >= max_x || min_y >= max_y) {
        return;
    }

    cv::Rect roi(min_x, min_y, max_x - min_x + 1, max_y - min_y + 1);

    cv::Mat line_img = cv::Mat::zeros(roi.size(), CV_8UC4);

    cv::Point2d start_roi(start.x - min_x, start.y - min_y);
    cv::Point2d end_roi(end.x - min_x, end.y - min_y);

    cv::line(
        line_img, cv::Point(cvRound(start_roi.x), cvRound(start_roi.y)),
        cv::Point(cvRound(end_roi.x), cvRound(end_roi.y)), string.color,
        thickness_rounded, cv::LINE_AA
    );

    cv::Mat image_roi = image(roi);

    float alpha = string.color[3] / 255.0f * (thickness / thickness_rounded);
    cv::addWeighted(line_img, alpha, image_roi, 1.0f - alpha, 0, image_roi);
}
