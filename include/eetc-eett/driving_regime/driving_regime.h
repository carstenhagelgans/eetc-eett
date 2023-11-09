#pragma once

#include <vector>

#include "eetc-eett/simulation/simulation_result.h"

#include "soro/rolling_stock/train_physics.h"
#include "soro/runtime/interval.h"
#include "soro/si/units.h"

namespace ee::driving_regime {

/**
 * Struct of a driving regime/instruction.
 *
 * A regime is valid from a starting to an ending point.
 * This local limitation allows a direct assignment of one or more intervals
 * describing the route/line properties.
 */
struct driving_regime {
  driving_regime(soro::si::length const start, soro::si::length const end,
                 soro::si::speed const vstart, soro::si::speed const vend,
                 soro::si::time const tstart, soro::si::time const tend,
                 std::vector<soro::runtime::interval> const& intervals)
      : start_(start),
        end_(end),
        vstart_(vstart),
        vend_(vend),
        tstart_(tstart),
        tend_(tend),
        intervals_(intervals) {}

  virtual ~driving_regime();

  driving_regime(driving_regime const&) = default;
  driving_regime& operator=(driving_regime const&) = default;

  driving_regime(driving_regime&&) = default;
  driving_regime& operator=(driving_regime&&) = default;

  soro::si::length start_{soro::si::INVALID<soro::si::length>};
  soro::si::length end_{soro::si::INVALID<soro::si::length>};
  soro::si::speed vstart_{soro::si::INVALID<soro::si::speed>};
  soro::si::speed vend_{soro::si::INVALID<soro::si::speed>};
  soro::si::time tstart_{soro::si::INVALID<soro::si::time>};
  soro::si::time tend_{soro::si::INVALID<soro::si::time>};

  soro::si::length step_{soro::si::INVALID<soro::si::length>};

  std::vector<soro::runtime::interval> intervals_{};

  /**
   * Runs a simulation of the current driving regime with given initial or final
   * velocity.
   *
   * @remark switches between simulate and simulate_on regarding the given
   * boolean parameter.
   *
   * @param tp a train described by an train_physics struct.
   * @param reverse choose whether the simulation runs in reverse mode or not,
   * default: false.
   * @return a vector of runtime_result structs representing the simulation
   * results.
   */
  std::vector<simulation::simulation_result> run(
      soro::rs::train_physics const& /* tp */, bool const reverse = false);

private:
  virtual std::vector<simulation::simulation_result> simulate(
      soro::rs::train_physics const& /* tp */) = 0;
  virtual std::vector<simulation::simulation_result> simulate_reverse(
      soro::rs::train_physics const& /* tp */) = 0;
};

}  // namespace ee::driving_regime
