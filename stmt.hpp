#pragma once

#include <vector>
#include <string>
#include <cstdint>

#include "stmt_enum.hpp"
#include "expr.hpp"

namespace dsp {

struct stmt_t
{
  virtual void accept(visitor_t<void> const * visitor) const = 0;
  virtual uint32_t accept(visitor_t<uint32_t> const * visitor) const = 0;
};

template <typename T>
struct stmt_accept_t : stmt_t {
    virtual void accept(visitor_t<void> const * visitor) const {
      return visitor->visit(static_cast<const T*>(this));
    }

    virtual uint32_t accept(visitor_t<uint32_t> const * visitor) const
    {
      return visitor->visit(static_cast<const T*>(this));
    }
};

template <bool S, int N>
struct imm_t {
  imm_t(const token_t& token, const expr_t * expr)
    : token(token), expr(expr) {}

  const token_t& token;
  const expr_t * expr;

  static constexpr bool sign = S;
  static constexpr int bits = N;
  static constexpr num_t max = (1L << (bits - static_cast<num_t>(sign))) - 1;
  static constexpr num_t min = sign ? -(max + 1) : 0;

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

namespace op {

static uint32_t op_mask(uint32_t mask) { return (0b11 << 30) | mask; }
static uint32_t op_code(uint32_t code) { return (0b00 << 30) | code; }

struct op_t
{
  virtual uint32_t mask() const = 0;
  virtual uint32_t code() const = 0;
  virtual uint32_t bits() const = 0;
};

struct alu_t : op_t, stmt_accept_t<alu_t>
{
  alu_t(alu_type_t type)
    : type(type) {}

  const alu_type_t type;

  uint32_t mask() const { return op_mask(0b1111 << 26); }
  uint32_t code() const { return op_code(0b0000 << 26); }
  uint32_t bits() const
  {
    switch (type) {
    case alu_type_t::andl: return 0b0001 << 26;
    case alu_type_t::orl:  return 0b0010 << 26;
    case alu_type_t::xorl: return 0b0011 << 26;
    case alu_type_t::add:  return 0b0100 << 26;
    case alu_type_t::sub:  return 0b0101 << 26;
    case alu_type_t::ad2:  return 0b0110 << 26;
    case alu_type_t::sr:   return 0b1000 << 26;
    case alu_type_t::rr:   return 0b1001 << 26;
    case alu_type_t::sl:   return 0b1010 << 26;
    case alu_type_t::rl:   return 0b1011 << 26;
    case alu_type_t::rl8:  return 0b1111 << 26;
    default: __builtin_unreachable();
    }
  }
};

static uint32_t xy_src_bits(xy_src_t src, int shift)
{
  using enum xy_src_t;

  switch (src) {
  case m0:  return 0b000 << shift;
  case m1:  return 0b001 << shift;
  case m2:  return 0b010 << shift;
  case m3:  return 0b011 << shift;
  case mc0: return 0b100 << shift;
  case mc1: return 0b101 << shift;
  case mc2: return 0b110 << shift;
  case mc3: return 0b111 << shift;
  default: __builtin_unreachable();
  }
}

struct mov_ram_x_t : op_t, stmt_accept_t<mov_ram_x_t>
{
  mov_ram_x_t(xy_src_t src)
    : src(src) {}

  const xy_src_t src;

  uint32_t mask() const { return op_mask(0b100'111 << 20); }
  uint32_t code() const { return op_code(0b100'000 << 20); }
  uint32_t bits() const { return xy_src_bits(src, 20);     }
};

struct mov_mul_p_t : op_t, stmt_accept_t<mov_mul_p_t>
{
  mov_mul_p_t() {}

  uint32_t mask() const { return op_mask(0b011'000 << 20); }
  uint32_t code() const { return op_code(0b010'000 << 20); }
  uint32_t bits() const { return 0;                        }
};

struct mov_ram_p_t : op_t, stmt_accept_t<mov_ram_p_t>
{
  mov_ram_p_t(xy_src_t src)
    : src(src) {}

  const xy_src_t src;

  uint32_t mask() const { return op_mask(0b011'111 << 20); }
  uint32_t code() const { return op_code(0b011'000 << 20); }
  uint32_t bits() const { return xy_src_bits(src, 20);     }
};

struct mov_ram_y_t : op_t, stmt_accept_t<mov_ram_y_t>
{
  mov_ram_y_t(xy_src_t src)
    : src(src) {}

  const xy_src_t src;

  uint32_t mask() const { return op_mask(0b100'111 << 14); }
  uint32_t code() const { return op_code(0b100'000 << 14); }
  uint32_t bits() const { return xy_src_bits(src, 14);     }
};

struct clr_a_t : op_t, stmt_accept_t<clr_a_t>
{
  clr_a_t() {}

  uint32_t mask() const { return op_mask(0b011'000 << 14); }
  uint32_t code() const { return op_code(0b001'000 << 14); }
  uint32_t bits() const { return 0;                        }
};

struct mov_alu_a_t : op_t, stmt_accept_t<mov_alu_a_t>
{
  mov_alu_a_t() {}

  uint32_t mask() const { return op_mask(0b011'000 << 14); }
  uint32_t code() const { return op_code(0b010'000 << 14); }
  uint32_t bits() const { return 0;                        }
};

struct mov_ram_a_t : op_t, stmt_accept_t<mov_ram_a_t>
{
  mov_ram_a_t(xy_src_t src)
    : src(src) {}

  const xy_src_t src;

  uint32_t mask() const { return op_mask(0b011'111 << 14); }
  uint32_t code() const { return op_code(0b011'000 << 14); }
  uint32_t bits() const { return xy_src_bits(src, 14);     }
};

static uint32_t d1_dest_bits(d1_dest_t dest)
{
  using enum d1_dest_t;

  switch (dest) {
  case mc0: return 0b0000 << 8;
  case mc1: return 0b0001 << 8;
  case mc2: return 0b0010 << 8;
  case mc3: return 0b0011 << 8;
  case rx:  return 0b0100 << 8;
  case pl:  return 0b0101 << 8;
  case ra0: return 0b0110 << 8;
  case wa0: return 0b0111 << 8;
  case lop: return 0b1010 << 8;
  case top: return 0b1011 << 8;
  case ct0: return 0b1100 << 8;
  case ct1: return 0b1101 << 8;
  case ct2: return 0b1110 << 8;
  case ct3: return 0b1111 << 8;
  default: __builtin_unreachable();
  }
}

static uint32_t d1_src_bits(d1_src_t src)
{
  using enum d1_src_t;

  switch (src) {
  case m0:  return 0b0000 << 0;
  case m1:  return 0b0001 << 0;
  case m2:  return 0b0010 << 0;
  case m3:  return 0b0011 << 0;
  case mc0: return 0b0100 << 0;
  case mc1: return 0b0101 << 0;
  case mc2: return 0b0110 << 0;
  case mc3: return 0b0111 << 0;
  case all: return 0b1001 << 0;
  case alh: return 0b1010 << 0;
  default: __builtin_unreachable();
  }
}

struct mov_imm_d1_t : op_t, stmt_accept_t<mov_imm_d1_t>
{
  mov_imm_d1_t(uimm_t<8> imm, d1_dest_t dest)
    : imm(imm), dest(dest) {}

  const uimm_t<8> imm;
  const d1_dest_t dest;

  uint32_t mask() const { return op_mask(0b11'1111'1111'1111 << 0); }
  uint32_t code() const { return op_code(0b01'0000'0000'0000 << 0); }
  uint32_t bits() const { return d1_dest_bits(dest);                }
};

struct mov_ram_d1_t : op_t, stmt_accept_t<mov_ram_d1_t>
{
  mov_ram_d1_t(d1_src_t src, d1_dest_t dest)
    : src(src), dest(dest) {}

  const d1_src_t src;
  const d1_dest_t dest;

  uint32_t mask() const { return op_mask(0b11'1111'0000'1111 << 0);     }
  uint32_t code() const { return op_code(0b11'0000'0000'0000 << 0);     }
  uint32_t bits() const { return d1_dest_bits(dest) | d1_src_bits(src); }
};

struct control_word_t : stmt_accept_t<control_word_t>
{
  control_word_t(std::vector<const op::op_t *> ops)
    : ops(ops)
  {
  }

  const std::vector<const op_t *> ops;

  uint32_t mask() const { return 0xffff'ffff;  }
  uint32_t code() const { return 0;            }
  uint32_t bits() const { return 0;            }
};

} // op

namespace load {

static uint32_t dest_bits(dest_t dest)
{
  using enum dest_t;

  switch (dest) {
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

static uint32_t cond_bits(cond_t cond)
{
  using enum cond_t;

  switch (cond) {
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

struct mvi_t : stmt_accept_t<mvi_t>
{
  mvi_t(uimm_t<25> imm, dest_t dest)
    : imm(imm), dest(dest) {}

  uint32_t mask() const { return 0xffff'ffff;       }
  uint32_t code() const { return 0b10'0000'0 << 25; }
  uint32_t bits() const { return dest_bits(dest);   }

  const uimm_t<25> imm;
  const dest_t dest;
};

struct mvi_cond_t : stmt_accept_t<mvi_cond_t>
{
  mvi_cond_t(uimm_t<19> imm, dest_t dest, cond_t cond)
    : imm(imm), dest(dest), cond(cond) {}

  const uimm_t<19> imm;
  const dest_t dest;
  const cond_t cond;

  uint32_t mask() const { return 0xffff'ffff;       }
  uint32_t code() const { return 0b10'0000'1 << 25; }
  uint32_t bits() const { return dest_bits(dest)
                         | cond_bits(cond);
                  }
};

} // load

namespace dma {

static uint32_t add_mode_bits(add_mode_t add)
{
  using enum add_mode_t;

  switch (add) {
  case _0 : return 0b000 << 15;
  case _1 : return 0b001 << 15;
  case _2 : return 0b010 << 15;
  case _4 : return 0b011 << 15;
  case _8 : return 0b100 << 15;
  case _16: return 0b101 << 15;
  case _32: return 0b110 << 15;
  case _64: return 0b111 << 15;
  default: __builtin_unreachable();
  }
}

static uint32_t hold_bits(bool hold)
{
  return hold ? (1 << 14)
              : (0 << 14)
              ;
}

static uint32_t src_bits(src_t src)
{
  using enum src_t;

  switch (src) {
  case m0 : return 0b000 << 8;
  case m1 : return 0b001 << 8;
  case m2 : return 0b010 << 8;
  case m3 : return 0b011 << 8;
  default: __builtin_unreachable();
  }
}

static uint32_t dst_bits(dst_t dst)
{
  using enum dst_t;

  switch (dst) {
  case m0 : return 0b000 << 8;
  case m1 : return 0b001 << 8;
  case m2 : return 0b010 << 8;
  case m3 : return 0b011 << 8;
  case prg: return 0b100 << 8;
  default: __builtin_unreachable();
  }
}

static uint32_t length_ram_bits(length_ram_t ram)
{
  using enum length_ram_t;

  switch (ram) {
  case m0 : return 0b000 << 0;
  case m1 : return 0b001 << 0;
  case m2 : return 0b010 << 0;
  case m3 : return 0b011 << 0;
  case mc0: return 0b100 << 0;
  case mc1: return 0b101 << 0;
  case mc2: return 0b110 << 0;
  case mc3: return 0b111 << 0;
  default: __builtin_unreachable();
  }
}

struct d0_dst_imm_t : stmt_accept_t<d0_dst_imm_t>
{
  d0_dst_imm_t(bool hold, add_mode_t add, dst_t dst, uimm_t<8> imm)
    : hold(hold), add(add), dst(dst), imm(imm) {}

  const bool hold;
  const add_mode_t add;
  const dst_t dst;
  const uimm_t<8> imm;

  uint32_t mask() const { return 0xffff'ffff;               }
  uint32_t code() const { return 0b1100 << 28 | 0b00 << 12; }
  uint32_t bits() const { return add_mode_bits(add)
                         | hold_bits(hold)
                         | dst_bits(dst);
                  }
};

struct src_d0_imm_t : stmt_accept_t<src_d0_imm_t>
{
  src_d0_imm_t(bool hold, add_mode_t add, src_t src, uimm_t<8> imm)
    : hold(hold), add(add), src(src), imm(imm) {}

  const bool hold;
  const add_mode_t add;
  const src_t src;
  const uimm_t<8> imm;

  uint32_t mask() const { return 0xffff'ffff;               }
  uint32_t code() const { return 0b1100 << 28 | 0b01 << 12; }
  uint32_t bits() const { return add_mode_bits(add)
                         | hold_bits(hold)
                         | src_bits(src);
                  }
};

struct d0_dst_ram_t : stmt_accept_t<d0_dst_ram_t>
{
  d0_dst_ram_t(bool hold, add_mode_t add, dst_t dst, length_ram_t ram)
    : hold(hold), add(add), dst(dst), ram(ram) {}

  const bool hold;
  const add_mode_t add;
  const dst_t dst;
  const length_ram_t ram;

  uint32_t mask() const { return 0xffff'ffff;               }
  uint32_t code() const { return 0b1100 << 28 | 0b10 << 12; }
  uint32_t bits() const { return add_mode_bits(add)
                         | hold_bits(hold)
                         | dst_bits(dst)
                         | length_ram_bits(ram);
                  }
};

struct src_d0_ram_t : stmt_accept_t<src_d0_ram_t>
{
  // from src to d0
  src_d0_ram_t(bool hold, add_mode_t add, src_t src, length_ram_t ram)
    : hold(hold), add(add), src(src), ram(ram) {}

  const bool hold;
  const add_mode_t add;
  const src_t src;
  const length_ram_t ram;

  uint32_t mask() const { return 0xffff'ffff;               }
  uint32_t code() const { return 0b1100 << 28 | 0b11 << 12; }
  uint32_t bits() const { return add_mode_bits(add)
                         | hold_bits(hold)
                         | src_bits(src)
                         | length_ram_bits(ram);
                  }
};

} // dma

namespace jump
{

static uint32_t cond_bits(cond_t cond)
{
  using enum cond_t;

  switch (cond) {
  case z  : return 0b100'001 << 19;
  case nz : return 0b000'001 << 19;
  case s  : return 0b100'010 << 19;
  case ns : return 0b000'010 << 19;
  case c  : return 0b100'100 << 19;
  case nc : return 0b000'100 << 19;
  case t0 : return 0b101'000 << 19;
  case nt0: return 0b001'000 << 19;
  case zs : return 0b100'011 << 19;
  case nzs: return 0b000'011 << 19;
  default: __builtin_unreachable();
  }
}

struct jmp_t : stmt_accept_t<jmp_t>
{
  jmp_t(uimm_t<8> imm)
    : imm(imm) {}

  const uimm_t<8> imm;

  uint32_t mask() const { return 0xffff'ffff;       }
  uint32_t code() const { return 0b1101'00'0 << 25; }
  uint32_t bits() const { return 0;                 }
};

struct jmp_cond_t : stmt_accept_t<jmp_cond_t>
{
  jmp_cond_t(cond_t cond, uimm_t<8> imm)
    : cond(cond), imm(imm) {}

  const cond_t cond;
  const uimm_t<8> imm;

  uint32_t mask() const { return 0xffff'ffff;       }
  uint32_t code() const { return 0b1101'00'1 << 25; }
  uint32_t bits() const { return cond_bits(cond);   }
};

} // jump

namespace loop {

struct btm_t : stmt_accept_t<btm_t>
{
  uint32_t mask() const { return 0xffff'ffff;    }
  uint32_t code() const { return 0b1110'0 << 27; }
  uint32_t bits() const { return 0;              }
};

struct lps_t : stmt_accept_t<lps_t>
{
  uint32_t mask() const { return 0xffff'ffff;    }
  uint32_t code() const { return 0b1110'1 << 27; }
  uint32_t bits() const { return 0;              }
};

} // loop

namespace end {

struct end_t : stmt_accept_t<end_t>
{
  uint32_t mask() const { return 0xffff'ffff;    }
  uint32_t code() const { return 0b1111'0 << 27; }
  uint32_t bits() const { return 0;              }
};

struct endi_t : stmt_accept_t<endi_t>
{
  uint32_t mask() const { return 0xffff'ffff;    }
  uint32_t code() const { return 0b1111'1 << 27; }
  uint32_t bits() const { return 0;              }
};

} // end

namespace nop {

struct nop_t : stmt_accept_t<nop_t>
{
  uint32_t mask() const { return 0xffff'ffff; }
  uint32_t code() const { return 0x0000'0000; }
  uint32_t bits() const { return 0;           }
};

}

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
