#pragma once

#include <vector>
#include <string>

#include "stmt_enum.hpp"
#include "expr.hpp"

namespace dsp {

struct stmt_t
{
  virtual void accept(visitor_t<void> const * visitor) const = 0;
  virtual std::string accept(visitor_t<std::string> const * visitor) const = 0;
};

template <typename T>
struct stmt_accept_t : stmt_t {
    virtual void accept(visitor_t<void> const * visitor) const {
      return visitor->visit(static_cast<const T*>(this));
    }

    virtual std::string accept(visitor_t<std::string> const * visitor) const
    {
      return visitor->visit(static_cast<const T*>(this));
    }
};

template <bool S, int N>
struct imm_t {
  imm_t(expr_t * expr)
    : expr(expr) {}

  const expr_t * expr;

  static constexpr bool sign = S;
  static constexpr int bits = N;
};

template <int N>
using simm_t = imm_t<true, N>;

template <int N>
using uimm_t = imm_t<false, N>;

namespace op {

struct op_t
{
};

struct alu_t : op_t, stmt_accept_t<alu_t>
{
  alu_t(alu_type_t type)
    : type(type) {}

  const alu_type_t type;
};

struct mov_ram_x_t : op_t, stmt_accept_t<mov_ram_x_t>
{
  mov_ram_x_t(xy_src_t src)
    : src(src) {}

  const xy_src_t src;
};

struct mov_mul_p_t : op_t, stmt_accept_t<mov_mul_p_t>
{
  mov_mul_p_t() {}
};

struct mov_ram_p_t : op_t, stmt_accept_t<mov_ram_p_t>
{
  mov_ram_p_t(xy_src_t src)
    : src(src) {}

  const xy_src_t src;
};

struct mov_ram_y_t : op_t, stmt_accept_t<mov_ram_y_t>
{
  mov_ram_y_t(xy_src_t src)
    : src(src) {}

  const xy_src_t src;
};

struct clr_a_t : op_t, stmt_accept_t<clr_a_t>
{
  clr_a_t() {}
};

struct mov_alu_a_t : op_t, stmt_accept_t<mov_alu_a_t>
{
  mov_alu_a_t() {}
};

struct mov_ram_a_t : op_t, stmt_accept_t<mov_ram_a_t>
{
  mov_ram_a_t(xy_src_t src)
    : src(src) {}

  const xy_src_t src;
};

struct mov_imm_d1_t : op_t, stmt_accept_t<mov_imm_d1_t>
{
  mov_imm_d1_t(simm_t<8> imm, d1_dest_t dest)
    : imm(imm), dest(dest) {}

  const simm_t<8> imm;
  const d1_dest_t dest;
};

struct mov_ram_d1_t : op_t, stmt_accept_t<mov_ram_d1_t>
{
  mov_ram_d1_t(d1_src_t src, d1_dest_t dest)
    : src(src), dest(dest) {}

  const d1_src_t src;
  const d1_dest_t dest;
};

struct control_word_t : stmt_accept_t<control_word_t>
{
  control_word_t(std::vector<const op_t *> ops)
    : ops(ops) {}

  const std::vector<const op_t *> ops;
};

} // op

namespace load {

struct mvi_t : stmt_accept_t<mvi_t>
{
  mvi_t(uimm_t<25> imm, dest_t dest)
    : imm(imm), dest(dest) {}

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
};

} // load

namespace dma {

struct src_d0_imm_t : stmt_accept_t<src_d0_imm_t>
{
  src_d0_imm_t(bool hold, add_mode_t add, src_t src, uimm_t<8> imm)
    : hold(hold), add(add), src(src), imm(imm) {}

  const bool hold;
  const add_mode_t add;
  const src_t src;
  const uimm_t<8> imm;
};

struct d0_dst_imm_t : stmt_accept_t<d0_dst_imm_t>
{
  d0_dst_imm_t(bool hold, add_mode_t add, dst_t dst, uimm_t<8> imm)
    : hold(hold), add(add), dst(dst), imm(imm) {}

  const bool hold;
  const add_mode_t add;
  const dst_t dst;
  const uimm_t<8> imm;
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
};

struct d0_dst_ram_t : stmt_accept_t<d0_dst_ram_t>
{
  d0_dst_ram_t(bool hold, add_mode_t add, dst_t dst, length_ram_t ram)
    : hold(hold), add(add), dst(dst), ram(ram) {}

  const bool hold;
  const add_mode_t add;
  const dst_t dst;
  const length_ram_t ram;
};

} // dma

namespace jump
{

struct jmp_t : stmt_accept_t<jmp_t>
{
  jmp_t(uimm_t<8> imm)
    : imm(imm) {}

  const uimm_t<8> imm;
};

struct jmp_cond_t : stmt_accept_t<jmp_cond_t>
{
  jmp_cond_t(cond_t cond, uimm_t<8> imm)
    : cond(cond), imm(imm) {}

  const cond_t cond;
  const uimm_t<8> imm;
};

} // jump

namespace loop {

struct btm_t : stmt_accept_t<btm_t>
{
};

struct lps_t : stmt_accept_t<lps_t>
{
};

} // loop

namespace end {

struct end_t : stmt_accept_t<end_t>
{
};

struct endi_t : stmt_accept_t<endi_t>
{
};

} // end

namespace nop {

struct nop_t : stmt_accept_t<nop_t>
{
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
