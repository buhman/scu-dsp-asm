#pragma once

#include "visitable.hpp"
#include "num.hpp"

namespace dsp {

template <typename T>
struct visitor_t
{
  virtual T visit(const unary_t * expr) const = 0;
  virtual T visit(const binary_t * expr) const = 0;
  virtual T visit(const grouping_t * expr) const = 0;
  virtual T visit(const literal_t * expr) const = 0;
};

}
