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

  virtual T visit(const op::alu_t * stmt) const = 0;
  virtual T visit(const op::mov_ram_x_t * mov_ram_x) const = 0;
  virtual T visit(const op::mov_mul_p_t * mov_mul_p) const = 0;
  virtual T visit(const op::mov_ram_p_t * mov_ram_p) const = 0;
  virtual T visit(const op::mov_ram_y_t * mov_ram_y) const = 0;
  virtual T visit(const op::clr_a_t * clr_a) const = 0;
  virtual T visit(const op::mov_alu_a_t * mov_alu_a) const = 0;
  virtual T visit(const op::mov_ram_a_t * mov_ram_a) const = 0;
  virtual T visit(const op::mov_imm_d1_t * mov_imm_) const = 0;
  virtual T visit(const op::mov_ram_d1_t * mov_ram_) const = 0;
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
};

}
