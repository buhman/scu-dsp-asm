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

  uint32_t mask() const { return 0xffff'ffff; }
  uint32_t code() const { return 0x0000'0000; }
  uint32_t bits() const { return 0;           }
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
