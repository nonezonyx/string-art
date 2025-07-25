#include "string_art/metrics/mse.hpp"
#include <boost/dll/alias.hpp>
#include <memory>
#include <opencv2/opencv.hpp>
#include <string>
#include "string_art/abstract_metric.hpp"

using namespace string_art;

std::string MSE::name() const {
    return "MSE";
}

double MSE::distance(const cv::Mat &lhs, const cv::Mat &rhs) const {
    cv::Mat diff = lhs - rhs;
    cv::Mat squaredDiff = diff.mul(diff);
    double sum = cv::sum(squaredDiff)[0];
    return -sum / squaredDiff.total();
}

std::shared_ptr<AbstractMetric> MSE::create() {
    return std::make_shared<MSE>();
}

BOOST_DLL_ALIAS(::string_art::MSE::create, create_metric)
