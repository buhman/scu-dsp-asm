#pragma once

#include <cstdint>

#include "imm.hpp"

namespace dsp {

template <typename T>
struct ins_t
{
  uint32_t render() const
  {
    return T::code() | T::bits();
  }

  static bool pred(uint32_t ins)
  {
    return (ins & T::mask()) == T::code();
  }
};

template <typename T, int N>
struct ins_imm_t : ins_t<T>
{
  ins_imm_t(uimm_t<N> imm)
    : imm(imm) {}

  const uimm_t<N> imm;

  uint32_t render(visitor_t<uint32_t> * visitor)
  {
    num_t value = imm.normalize(imm.expr->accept(visitor));
    if (imm.in_range(value))
      return render() | value;
    else
      throw imm_out_of_range(imm, value);
  }
};

}
