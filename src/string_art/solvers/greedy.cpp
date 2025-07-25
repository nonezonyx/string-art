#include "string_art/solvers/greedy.hpp"
#include <memory>
#include "string_art/abstract_metric.hpp"
#include "string_art/abstract_solver.hpp"
#include "string_art/string_art.hpp"

using namespace string_art;

GreedySolver::GreedySolver(
    const Metadata &metadata,
    const progress_callback &progress
)
    : metadata_(metadata), progress_(progress) {
}

std::string GreedySolver::name() const {
    return "Greedy";
}

const Metadata &GreedySolver::get_metadata() const {
    return metadata_;
}

StringArtPattern GreedySolver::solve(
    const cv::Mat &image,
    std::shared_ptr<AbstractMetric> metric
) {
    StringArtPattern pattern;
    cv::Mat curr(image.size(), CV_8UC3, metadata_.background_color);
    // TODO
    return pattern;
}

std::shared_ptr<AbstractSolver> GreedySolver::create(
    const Metadata &metadata,
    const progress_callback &progress
) {
    return std::make_shared<GreedySolver>(metadata, progress);
}
