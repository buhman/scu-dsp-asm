#include <cstdint>

#include "imm.hpp"
#include "stmt_base.hpp"

namespace dsp {

template <typename T>
struct ins_t
{
  virtual uint32_t bits() const;

  uint32_t render() const
  {
    return T::code() | bits();
  }

  constexpr bool pred(uint32_t ins) const
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

namespace load {

struct dest_t {
  enum value_t {
    mc0, mc1, mc2, mc3,
    rx , pl ,
    ra0, wa0,
    lop, pc ,
  };

  const value_t value;

  constexpr dest_t(value_t value)
    : value(value) {}

  constexpr dest_t(uint32_t code)
    : value(to_value(code)) { }

  static constexpr uint32_t mask() { return 0b1111 << 26; }

  static constexpr value_t to_value(uint32_t code)
  {
    using enum value_t;

    switch (code & mask()) {
    case 0b0000 << 26: return mc0;
    case 0b0001 << 26: return mc1;
    case 0b0010 << 26: return mc2;
    case 0b0011 << 26: return mc3;
    case 0b0100 << 26: return rx;
    case 0b0101 << 26: return pl;
    case 0b0110 << 26: return ra0;
    case 0b0111 << 26: return wa0;
    case 0b1010 << 26: return lop;
    case 0b1100 << 26: return pc;
    default:
      std::cerr << "invalid load dest code: " << (code & mask()) << std::endl;
      throw std::runtime_error("invalid code");
    }
  }

  uint32_t bits() const
  {
    using enum value_t;

    switch (value) {
    case mc0: return 0b0000 << 26;
    case mc1: return 0b0001 << 26;
    case mc2: return 0b0010 << 26;
    case mc3: return 0b0011 << 26;
    case rx:  return 0b0100 << 26;
    case pl:  return 0b0101 << 26;
    case ra0: return 0b0110 << 26;
    case wa0: return 0b0111 << 26;
    case lop: return 0b1010 << 26;
    case pc:  return 0b1100 << 26;
    default: __builtin_unreachable();
    }
  }
};

struct cond_t {
  enum value_t {
    z , nz ,
    s , ns ,
    c , nc ,
    t0, nt0,
    zs, nzs,
  };

  const value_t value;

  constexpr cond_t(value_t value)
    : value(value) {}

  constexpr cond_t(uint32_t code)
    : value(to_value(code)) { }

  static constexpr uint32_t mask() { return 0b1'0'1111 << 19; }

  static constexpr value_t to_value(uint32_t code)
  {
    using enum value_t;

    switch (code & mask()) {
    case 0b1'0'0001 << 19: return z;
    case 0b0'0'0001 << 19: return nz;
    case 0b1'0'0010 << 19: return s;
    case 0b0'0'0010 << 19: return ns;
    case 0b1'0'0100 << 19: return c;
    case 0b0'0'0100 << 19: return nc;
    case 0b1'0'1000 << 19: return t0;
    case 0b0'0'1000 << 19: return nt0;
    case 0b1'0'0011 << 19: return zs;
    case 0b0'0'0011 << 19: return nzs;
    default:
      std::cerr << "invalid load cond code: " << (code & mask()) << std::endl;
      throw std::runtime_error("invalid code");
    }
  }

  uint32_t bits() const
  {
    using enum value_t;

    switch (value) {
    case z:   return 0b1'0'0001 << 19;
    case nz:  return 0b0'0'0001 << 19;
    case s:   return 0b1'0'0010 << 19;
    case ns:  return 0b0'0'0010 << 19;
    case c:   return 0b1'0'0100 << 19;
    case nc:  return 0b0'0'0100 << 19;
    case t0:  return 0b1'0'1000 << 19;
    case nt0: return 0b0'0'1000 << 19;
    case zs:  return 0b1'0'0011 << 19;
    case nzs: return 0b0'0'0011 << 19;
    default: __builtin_unreachable();
    }
  }
};

struct mvi_cond_t : stmt_accept_t<mvi_cond_t>, ins_imm_t<mvi_cond_t, 19>
{
  using imm_type = uimm_t<19>;

  mvi_cond_t(dest_t dest, cond_t cond, imm_type imm)
    : dest(dest), cond(cond), ins_imm_t(imm)
  { }

  mvi_cond_t(uint32_t code)
    : dest(code), cond(code), ins_imm_t(code)
  { }

  const dest_t dest;
  const cond_t cond;

  static uint32_t mask() { return 0b11'0000'1 << 25; }
  static uint32_t code() { return 0b10'0000'1 << 25; }
  uint32_t bits() const { return dest.bits()
                               | cond.bits();
                        }
};

}

}
