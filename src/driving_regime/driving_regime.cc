#include "eetc-eett/driving_regime/driving_regime.h"

#include "utl/to_vec.h"

namespace ee::driving_regime {

driving_regime::~driving_regime() = default;

std::vector<simulation::simulation_result> driving_regime::run(
    soro::rs::train_physics const& tp, bool const reverse) {
  auto srs_tmp = std::vector<simulation::simulation_result>{};
  auto srs_result = std::vector<simulation::simulation_result>{};
  if (reverse) {
    srs_tmp = simulate_reverse(tp);
  } else {
    srs_tmp = simulate(tp);
  }

  for (auto const& sr_tmp : srs_tmp) {
    if (sr_tmp.is_valid()) {
      srs_result.emplace_back(sr_tmp);
    }
  }

  return srs_result;
}

}  // namespace ee::driving_regime
