#pragma once

#include <cstdint>

#include "ins.hpp"
#include "stmt_base.hpp"

namespace dsp {

namespace nop {

struct nop_t : stmt_accept_t<nop_t>, ins_t<nop_t>
{
  nop_t()
  {}

  nop_t(uint32_t code)
  {
    (void)code;
  }

  static constexpr uint32_t mask() { return 0xffff'ffff; }
  static constexpr uint32_t code() { return 0x0000'0000; }
  static constexpr uint32_t bits() { return 0;           }
};

} // namespace nop

struct assign_t : stmt_accept_t<assign_t>
{
  assign_t(token_t name, expr_t * value)
    : name(name), value(value) {}

  const token_t name;
  const expr_t * value;
};

struct label_t : stmt_accept_t<label_t>
{
  label_t(token_t name)
    : name(name) {}

  const token_t name;
};

} // dsp
