#pragma once

#include <functional>
#include <iosfwd>
#include <istream>
#include <opencv2/core/types.hpp>
#include <opencv2/opencv.hpp>
#include <string>
#include <unordered_map>
#include <vector>

namespace string_art {
enum class Action {
    CONNECT,
    CHANGE_COLOR,
};

const std::unordered_map<Action, std::string> action2string = {
    {Action::CONNECT, "CONNECT"},
    {Action::CHANGE_COLOR, "CHANGE_COLOR"}
};

struct Step {
    Action action;
    int value;
};

struct String {
    static constexpr float THICKNESS_EPSILON = 0.001f;
    cv::Scalar color = {0, 0, 0, 255};
    float thickness = 1.0f;  // string thickness in milimeters

    bool operator==(const String &other) const;
};

std::ostream &operator<<(std::ostream &os, const String &string);
std::istream &operator>>(std::istream &is, String &string);

struct Metadata {
    cv::Scalar background_color = {255, 255, 255, 255};  // canvas background color
    int lines = 2500;                                    // max number of lines
    int canvas_width = 4096;                             // canvas width in pixels
    int canvas_height = 4096;                            // canvas height in pixels
    float pixel_length = 1.0f;                           // canvas pixel length in milimeters
    std::vector<String> pallete;                         // strings colors
    std::vector<cv::Point2d> positions;                  // nails positions

    bool operator==(const Metadata &other) const;
};

std::ostream &operator<<(std::ostream &os, const Metadata &metadata);
std::istream &operator>>(std::istream &is, Metadata &metadata);

void add_string(
    cv::Mat &image,
    const cv::Point2d &start,
    const cv::Point2d &end,
    const String &string,
    float pixel_length
);

class StringArtPattern {
private:
    std::vector<Step> steps_;
    int current_color_ = 0;
    int current_position_ = 0;

public:
    cv::Mat to_image(const Metadata &metadata) const;
    void add_step(const Step &step);
};

// progress in percentage [0, 100]
using progress_callback = std::function<void(float)>;

}  // namespace string_art
