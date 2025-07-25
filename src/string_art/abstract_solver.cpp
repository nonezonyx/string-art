#include "string_art/abstract_solver.hpp"
#include <memory>
#include "string_art/string_art.hpp"

using namespace string_art;

std::shared_ptr<AbstractSolver>
create(const Metadata &metadata, const progress_callback &progress) {
    std::ignore = metadata;
    std::ignore = progress;
    return nullptr;
}
