#include "eetc-eett/simulation/simulation_result.h"

namespace ee::simulation {

bool simulation_result::is_valid() const {
  auto const all_valid = position_ != soro::si::INVALID<soro::si::length> &&
                         time_ != soro::si::INVALID<soro::si::time> &&
                         speed_ != soro::si::INVALID<soro::si::speed>;
  auto const all_positive = position_ >= soro::si::length{0.} &&
                            time_ >= soro::si::time{0.} &&
                            speed_ >= soro::si::speed{0.};

  return all_valid && all_positive;
}

bool is_valid(std::vector<simulation_result> const& srs) {
  for (auto const sr : srs) {
    if (!sr.is_valid()) {
      return false;
    }
  }

  for (auto i = std::size_t{0U}; i < srs.size() - 1; ++i) {
    if (srs[i].position_ <= srs[i + 1].position_) {
      return false;
    }

    if (srs[i].time_ <= srs[i + 1].time_) {
      return false;
    }
  }

  return true;
}

}  // namespace ee::simulation