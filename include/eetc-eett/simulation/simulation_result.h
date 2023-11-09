#pragma once

#include "soro/runtime/runtime_physics.h"
#include "soro/si/units.h"

namespace ee::simulation {

struct simulation_result {
  simulation_result() = default;
  simulation_result(soro::si::length position, soro::si::time const time,
                    soro::si::speed speed)
      : position_(position), time_(time), speed_(speed) {}
  simulation_result(soro::runtime_result const& rr)
      : position_(rr.distance_), time_(rr.time_), speed_(rr.speed_) {}

  // Checks whether this simulation_result is valid or not. A simulation_result
  // is considered valid, iff all data is valid and holds a number greater or
  // equal to zero.
  bool is_valid() const;

  soro::si::length position_{soro::si::INVALID<soro::si::length>};
  soro::si::time time_{soro::si::INVALID<soro::si::time>};
  soro::si::speed speed_{soro::si::INVALID<soro::si::speed>};
};


/**
 * Checks whether a vector of simulation_result structs is valid or not.
 * The given vector is considered invalid, if one holds:
 * - at least on simulation_result is invalid.
 * - pos_a > pos_b does not apply to two consecutive results.
 * - time_a > time_b does not apply to two consecutive results.
 */
bool is_valid(std::vector<simulation_result> const&);

}  // namespace ee::simulation
