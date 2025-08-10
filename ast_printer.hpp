#pragma once

#include <ostream>
#include <string_view>

#include "visitor.hpp"
#include "expr.hpp"
#include "num.hpp"
#include "stmt.hpp"
#include "stmt_ins.hpp"

namespace dsp {

namespace ast {

struct printer_t : visitor_t<void>
{
  printer_t(std::ostream& os)
    : os(os) {}

  std::ostream& os;

  void insert_indent(int current_type) const;

  void visit(const binary_t * binary) const;
  void visit(const grouping_t * grouping) const;
  void visit(const identifier_t * identifier) const;
  void visit(const literal_t * literal) const;
  void visit(const unary_t * unary) const;

  void visit(const op::andl_t * andl) const;
  void visit(const op::orl_t * orl) const;
  void visit(const op::xorl_t * xorl) const;
  void visit(const op::add_t * add) const;
  void visit(const op::sub_t * sub) const;
  void visit(const op::ad2_t * ad2) const;
  void visit(const op::sr_t * sr) const;
  void visit(const op::rr_t * rr) const;
  void visit(const op::sl_t * sl) const;
  void visit(const op::rl_t * rl) const;
  void visit(const op::rl8_t * rl8) const;

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

  void parenthesize(const std::string_view s, const expr_t * a) const;
  void parenthesize(const std::string_view s1, const std::string_view s2, const expr_t * a) const;
  void parenthesize(const std::string_view s1, const std::string_view s2, const std::string_view s3, const expr_t * a) const;
  void parenthesize(const std::string_view s1, const expr_t * a, const std::string_view s2) const;
  void parenthesize(const std::string_view s1, const expr_t * a, const std::string_view s2, const std::string_view s3) const;
  void parenthesize(const std::string_view s, const expr_t * a, const expr_t * b) const;
  void parenthesize(const std::string_view s) const;
  void parenthesize(const std::string_view s1, const std::string_view s2) const;
  void parenthesize(const std::string_view s1, const std::string_view s2, const std::string_view s3) const;
  void parenthesize(const std::string_view s1, const std::string_view s2, const std::string_view s3, const std::string_view s4) const;
};

}

}
