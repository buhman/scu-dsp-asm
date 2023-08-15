#pragma once

#include "visitable.hpp"
#include "num.hpp"

namespace dsp {

template <typename T>
struct visitor_t
{
  virtual T visit(const assign_t * expr) const = 0;
  virtual T visit(const literal_t * expr) const = 0;
};

}
