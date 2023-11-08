#pragma once

#include "cista/containers/vector.h"
#include "cista/reflection/comparable.h"

#include <cstddef>
#include <vector>

namespace ee::precomputation {

template <typename X>
struct expanded_parameter {
  expanded_parameter(X from, X to, X step) { init(from, to, step); }
  explicit expanded_parameter(std::vector<X> const& data)
      : data_(std::move(data)) {}

  X get() { return data_.at(current_); }

  bool next() {
    if (current_ == data_.size() - 1) {
      current_ = std::size_t{0};
      return true;
    }
    ++current_;
    return false;
  }

  std::size_t size() { return data_.size(); }

  std::vector<X> data_{};
  std::size_t current_{0};

private:
  void init(X from, X to, X step) {
    data_ = std::vector<X>{};

    X val = from;
    while (val <= to) {
      data_.emplace_back(val);
      val += step;
    }
  }
};

}  // namespace ee::precomputation
