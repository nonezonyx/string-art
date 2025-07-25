#pragma once

#include <opencv2/opencv.hpp>
#include "string_art/abstract_metric.hpp"

namespace string_art {
class MSE : public AbstractMetric {
public:
    MSE() = default;
    ~MSE() = default;

    std::string name() const override;
    double distance(const cv::Mat &lhs, const cv::Mat &rhs) const override;
    static std::shared_ptr<AbstractMetric> create();
};
}  // namespace string_art
