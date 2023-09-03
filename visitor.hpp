#pragma once

#include "visitable.hpp"
#include "num.hpp"

namespace dsp {

template <typename T>
struct visitor_t
{
  virtual T visit(const binary_t * expr) const = 0;
  virtual T visit(const grouping_t * expr) const = 0;
  virtual T visit(const identifier_t * expr) const = 0;
  virtual T visit(const literal_t * expr) const = 0;
  virtual T visit(const unary_t * expr) const = 0;

  virtual T visit(const op::andl_t * andl) const = 0;
  virtual T visit(const op::orl_t * orl) const = 0;
  virtual T visit(const op::xorl_t * xorl) const = 0;
  virtual T visit(const op::add_t * add) const = 0;
  virtual T visit(const op::sub_t * sub) const = 0;
  virtual T visit(const op::ad2_t * ad2) const = 0;
  virtual T visit(const op::sr_t * sr) const = 0;
  virtual T visit(const op::rr_t * rr) const = 0;
  virtual T visit(const op::sl_t * sl) const = 0;
  virtual T visit(const op::rl_t * rl) const = 0;
  virtual T visit(const op::rl8_t * rl8) const = 0;

  virtual T visit(const op::mov_ram_x_t * mov_ram_x) const = 0;
  virtual T visit(const op::mov_mul_p_t * mov_mul_p) const = 0;
  virtual T visit(const op::mov_ram_p_t * mov_ram_p) const = 0;
  virtual T visit(const op::mov_ram_y_t * mov_ram_y) const = 0;
  virtual T visit(const op::clr_a_t * clr_a) const = 0;
  virtual T visit(const op::mov_alu_a_t * mov_alu_a) const = 0;
  virtual T visit(const op::mov_ram_a_t * mov_ram_a) const = 0;
  virtual T visit(const op::mov_imm_d1_t * mov_imm_d1) const = 0;
  virtual T visit(const op::mov_ram_d1_t * mov_ram_d1) const = 0;

  virtual T visit(const op::control_word_t * control_word) const = 0;

  virtual T visit(const load::mvi_t * mvi) const = 0;
  virtual T visit(const load::mvi_cond_t * mvi_cond) const = 0;

  virtual T visit(const dma::src_d0_imm_t * src_d0_imm) const = 0;
  virtual T visit(const dma::d0_dst_imm_t * d0_dst_imm) const = 0;
  virtual T visit(const dma::src_d0_ram_t * src_d0_ram) const = 0;
  virtual T visit(const dma::d0_dst_ram_t * d0_dst_ram) const = 0;

  virtual T visit(const jump::jmp_t * jmp) const = 0;
  virtual T visit(const jump::jmp_cond_t * jmp_cond) const = 0;

  virtual T visit(const loop::btm_t * btm) const = 0;
  virtual T visit(const loop::lps_t * lps) const = 0;

  virtual T visit(const end::end_t * end) const = 0;
  virtual T visit(const end::endi_t * endi) const = 0;

  virtual T visit(const nop::nop_t * nop) const = 0;

  virtual T visit(const assign_t * assign) const = 0;
  virtual T visit(const label_t * label) const = 0;
};

}
