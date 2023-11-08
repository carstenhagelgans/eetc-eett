#include "doctest/doctest.h"

#include <algorithm>
#include <vector>

#include "eetc-eett/precomputation/expanded_parameter.h"

#include "soro/si/units.h"

TEST_SUITE_BEGIN("expanded_parameter");

TEST_CASE("expanded_parameter::base-unit::init") {
  double const from{0};
  double const to{10};
  double const step{1};

  auto const exp_length =
      ee::precomputation::expanded_parameter<double>(from, to, step);

  auto const should_exp_length =
      ee::precomputation::expanded_parameter<double>(std::vector<double>{
          0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0});

  CHECK_EQ(exp_length.current_, should_exp_length.current_);

  CHECK(std::equal(exp_length.data_.begin(), exp_length.data_.end(),
                   should_exp_length.data_.begin()));
}

TEST_CASE("expanded_parameter::si-unit::init") {
  soro::si::length const from{0};
  soro::si::length const to{10};
  soro::si::length const step{1};

  auto const exp_length =
      ee::precomputation::expanded_parameter<soro::si::length>(from, to, step);

  auto const should_exp_length =
      ee::precomputation::expanded_parameter<soro::si::length>(
          std::vector<soro::si::length>{
              {0}, {1}, {2}, {3}, {4}, {5}, {6}, {7}, {8}, {9}, {10}});

  CHECK_EQ(exp_length.current_, should_exp_length.current_);

  CHECK(std::equal(exp_length.data_.begin(), exp_length.data_.end(),
                   should_exp_length.data_.begin()));
}

TEST_SUITE_END();
