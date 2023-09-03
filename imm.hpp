#pragma once

#include "expr.hpp"

namespace dsp {

static const token_t null_token;

template <bool S, int N>
struct imm_t {
  imm_t(const token_t& token, const expr_t * expr)
    : token(token), expr(expr) {}

  imm_t(const uint32_t code)
    : token(null_token), expr(new literal_t(code & mask)) {}

  const token_t& token;
  const expr_t * expr;

  static constexpr bool sign = S;
  static constexpr int bits = N;
  static constexpr num_t max = (1L << (bits - static_cast<num_t>(sign))) - 1;
  static constexpr num_t min = sign ? -(max + 1) : 0;
  static constexpr num_t mask = (1L << bits) - 1;

  num_t normalize(num_t value) const
  {
    if (!S && value > 2147483648) { // fixme: hack
      return value & max;
    } else {
      return value;
    }
  }

  bool in_range(num_t value) const
  {
    return value <= max && value >= min;
  }
};

template <int N>
using simm_t = imm_t<true, N>;

template <int N>
using uimm_t = imm_t<false, N>;

}
