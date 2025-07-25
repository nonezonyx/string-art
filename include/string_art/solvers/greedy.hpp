#pragma once

#include <sys/stat.h>
#include <opencv2/opencv.hpp>
#include "string_art/abstract_metric.hpp"
#include "string_art/abstract_solver.hpp"

namespace string_art {
class GreedySolver : public AbstractSolver {
public:
    GreedySolver(const Metadata &metadata, const progress_callback &progress);
    ~GreedySolver() = default;

    std::string name() const override;
    const Metadata &get_metadata() const override;
    StringArtPattern solve(
        const cv::Mat &image,
        std::shared_ptr<AbstractMetric> metric
    ) override;

    static std::shared_ptr<AbstractSolver>
    create(const Metadata &metadata, const progress_callback &progress);

private:
    Metadata metadata_;
    progress_callback progress_;
};
}  // namespace string_art
