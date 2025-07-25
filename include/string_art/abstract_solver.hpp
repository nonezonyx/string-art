#pragma once

#include <boost/config.hpp>
#include <memory>
#include <opencv2/opencv.hpp>
#include <string>
#include "string_art/abstract_metric.hpp"
#include "string_art/string_art.hpp"

namespace string_art {
class BOOST_SYMBOL_VISIBLE AbstractSolver {
public:
    virtual ~AbstractSolver() = default;

    virtual std::string name() const = 0;
    virtual const Metadata &get_metadata() const = 0;
    virtual StringArtPattern
    solve(const cv::Mat &image, std::shared_ptr<AbstractMetric> metric) = 0;

    static std::shared_ptr<AbstractSolver>
    create(const Metadata &metadata, const progress_callback &progress);
};
}  // namespace string_art
