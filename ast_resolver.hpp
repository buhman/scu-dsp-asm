#pragma once

#include <ostream>
#include <string>
#include <cstdint>
#include <unordered_map>

#include "visitor.hpp"
#include "expr.hpp"
#include "stmt.hpp"
#include "ast.hpp"

namespace dsp {

namespace ast {

struct pc_t
{
  pc_t()
    : value() {}

  uint32_t value;
  void increment() { value += 1; }
};

struct resolver_t : visitor_t<void>
{
  resolver_t(pc_t& pc, variables_t& variables)
    : pc(pc), variables(variables) {}

  pc_t& pc;
  variables_t& variables;

  void visit(const binary_t * binary) const;
  void visit(const grouping_t * grouping) const;
  void visit(const identifier_t * identifier) const;
  void visit(const literal_t * literal) const;
  void visit(const unary_t * unary) const;

  void visit(const op::alu_t * alu) const;
  void visit(const op::mov_ram_x_t * mov_ram_x) const;
  void visit(const op::mov_mul_p_t * mov_mul_p) const;
  void visit(const op::mov_ram_p_t * mov_ram_p) const;
  void visit(const op::mov_ram_y_t * mov_ram_y) const;
  void visit(const op::clr_a_t * clr_a) const;
  void visit(const op::mov_alu_a_t * mov_alu_a) const;
  void visit(const op::mov_ram_a_t * mov_ram_a) const;
  void visit(const op::mov_imm_d1_t * mov_imm_d1) const;
  void visit(const op::mov_ram_d1_t * mov_ram_d1) const;
  void visit(const op::control_word_t * control_word) const;

  void visit(const load::mvi_t * mvi) const;
  void visit(const load::mvi_cond_t * mvi_cond) const;

  void visit(const dma::src_d0_imm_t * src_d0_imm) const;
  void visit(const dma::d0_dst_imm_t * d0_dst_imm) const;
  void visit(const dma::src_d0_ram_t * src_d0_ram) const;
  void visit(const dma::d0_dst_ram_t * d0_dst_ram) const;

  void visit(const jump::jmp_t * jmp) const;
  void visit(const jump::jmp_cond_t * jmp_cond) const;

  void visit(const loop::btm_t * btm) const;
  void visit(const loop::lps_t * lps) const;

  void visit(const end::end_t * end) const;
  void visit(const end::endi_t * endi) const;

  void visit(const nop::nop_t * nop) const;

  void visit(const assign_t * assign) const;
  void visit(const label_t * label) const;
};

}

}
