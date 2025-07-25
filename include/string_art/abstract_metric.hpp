#pragma once

#include <boost/config.hpp>
#include <memory>
#include <opencv2/opencv.hpp>
#include <string>

namespace string_art {
class BOOST_SYMBOL_VISIBLE AbstractMetric {
public:
    virtual ~AbstractMetric() = default;

    virtual std::string name() const = 0;
    virtual double distance(const cv::Mat &lhs, const cv::Mat &rhs) const = 0;

    static std::shared_ptr<AbstractMetric> create();
};
}  // namespace string_art
