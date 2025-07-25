#include "string_art/abstract_metric.hpp"
#include <memory>

using namespace string_art;

std::shared_ptr<AbstractMetric> AbstractMetric::create() {
    return nullptr;
}
