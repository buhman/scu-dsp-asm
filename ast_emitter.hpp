#pragma once

#include <ostream>
#include <string>
#include <cstdint>

#include "visitor.hpp"
#include "expr.hpp"
#include "stmt.hpp"
#include "ast.hpp"

namespace dsp {

namespace ast {

struct emitter_error_t : std::runtime_error
{
  emitter_error_t(const std::string& msg)
    : std::runtime_error(msg)
  { }
};

struct emitter_t : visitor_t<uint32_t>
{
  emitter_t(variables_t& variables, const addresses_t& addresses)
    : variables(variables), addresses(addresses) {}

  variables_t& variables;
  const addresses_t& addresses;

  uint32_t visit(const binary_t * binary) const;
  uint32_t visit(const grouping_t * grouping) const;
  uint32_t visit(const identifier_t * identifier) const;
  uint32_t visit(const literal_t * literal) const;
  uint32_t visit(const unary_t * unary) const;

  uint32_t visit(const op::alu_t * alu) const;
  uint32_t visit(const op::mov_ram_x_t * mov_ram_x) const;
  uint32_t visit(const op::mov_mul_p_t * mov_mul_p) const;
  uint32_t visit(const op::mov_ram_p_t * mov_ram_p) const;
  uint32_t visit(const op::mov_ram_y_t * mov_ram_y) const;
  uint32_t visit(const op::clr_a_t * clr_a) const;
  uint32_t visit(const op::mov_alu_a_t * mov_alu_a) const;
  uint32_t visit(const op::mov_ram_a_t * mov_ram_a) const;
  uint32_t visit(const op::mov_imm_d1_t * mov_imm_d1) const;
  uint32_t visit(const op::mov_ram_d1_t * mov_ram_d1) const;
  uint32_t visit(const op::control_word_t * control_word) const;

  uint32_t visit(const load::mvi_t * mvi) const;
  uint32_t visit(const load::mvi_cond_t * mvi_cond) const;

  uint32_t visit(const dma::src_d0_imm_t * src_d0_imm) const;
  uint32_t visit(const dma::d0_dst_imm_t * d0_dst_imm) const;
  uint32_t visit(const dma::src_d0_ram_t * src_d0_ram) const;
  uint32_t visit(const dma::d0_dst_ram_t * d0_dst_ram) const;

  uint32_t visit(const jump::jmp_t * jmp) const;
  uint32_t visit(const jump::jmp_cond_t * jmp_cond) const;

  uint32_t visit(const loop::btm_t * btm) const;
  uint32_t visit(const loop::lps_t * lps) const;

  uint32_t visit(const end::end_t * end) const;
  uint32_t visit(const end::endi_t * endi) const;

  uint32_t visit(const nop::nop_t * nop) const;

  uint32_t visit(const assign_t * assign) const;
  uint32_t visit(const label_t * label) const;
};

}

}
