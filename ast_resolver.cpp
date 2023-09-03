#include "ast_resolver.hpp"

namespace dsp {

namespace ast {

// expressions

void resolver_t::visit(const binary_t * binary) const
{
  (void)binary;
}

void resolver_t::visit(const grouping_t * grouping) const
{
  (void)grouping;
}

void resolver_t::visit(const identifier_t * identifier) const
{
  (void)identifier;
}

void resolver_t::visit(const literal_t * literal) const
{
  (void)literal;
}

void resolver_t::visit(const unary_t * unary) const
{
  (void)unary;
}

// instructions

void resolver_t::visit(const op::andl_t * andl) const
{
  (void)andl;
}

void resolver_t::visit(const op::orl_t * orl) const
{
  (void)orl;
}

void resolver_t::visit(const op::xorl_t * xorl) const
{
  (void)xorl;
}

void resolver_t::visit(const op::add_t * add) const
{
  (void)add;
}

void resolver_t::visit(const op::sub_t * sub) const
{
  (void)sub;
}

void resolver_t::visit(const op::ad2_t * ad2) const
{
  (void)ad2;
}

void resolver_t::visit(const op::sr_t * sr) const
{
  (void)sr;
}

void resolver_t::visit(const op::rr_t * rr) const
{
  (void)rr;
}

void resolver_t::visit(const op::sl_t * sl) const
{
  (void)sl;
}

void resolver_t::visit(const op::rl_t * rl) const
{
  (void)rl;
}

void resolver_t::visit(const op::rl8_t * rl8) const
{
  (void)rl8;
}

void resolver_t::visit(const op::mov_ram_x_t * mov_ram_x) const
{
  (void)mov_ram_x;
}

void resolver_t::visit(const op::mov_mul_p_t * mov_mul_p) const
{
  (void)mov_mul_p;
}

void resolver_t::visit(const op::mov_ram_p_t * mov_ram_p) const
{
  (void)mov_ram_p;
}

void resolver_t::visit(const op::mov_ram_y_t * mov_ram_y) const
{
  (void)mov_ram_y;
}

void resolver_t::visit(const op::clr_a_t * clr_a) const
{
  (void)clr_a;
}

void resolver_t::visit(const op::mov_alu_a_t * mov_alu_a) const
{
  (void)mov_alu_a;
}

void resolver_t::visit(const op::mov_ram_a_t * mov_ram_a) const
{
  (void)mov_ram_a;
}

void resolver_t::visit(const op::mov_imm_d1_t * mov_imm_d1) const
{
  (void)mov_imm_d1;
}

void resolver_t::visit(const op::mov_ram_d1_t * mov_ram_d1) const
{
  (void)mov_ram_d1;
}

void resolver_t::visit(const op::control_word_t * control_word) const
{
  (void)control_word;
  pc.increment();
}

void resolver_t::visit(const load::mvi_t * mvi) const
{
  (void)mvi;
  pc.increment();
}

void resolver_t::visit(const load::mvi_cond_t * mvi_cond) const
{
  (void)mvi_cond;
  pc.increment();
}

void resolver_t::visit(const dma::src_d0_imm_t * src_d0_imm) const
{
  (void)src_d0_imm;
  pc.increment();
}

void resolver_t::visit(const dma::d0_dst_imm_t * d0_dst_imm) const
{
  (void)d0_dst_imm;
  pc.increment();
}

void resolver_t::visit(const dma::src_d0_ram_t * src_d0_ram) const
{
  (void)src_d0_ram;
  pc.increment();
}

void resolver_t::visit(const dma::d0_dst_ram_t * d0_dst_ram) const
{
  (void)d0_dst_ram;
  pc.increment();
}

void resolver_t::visit(const jump::jmp_t * jmp) const
{
  (void)jmp;
  pc.increment();
}

void resolver_t::visit(const jump::jmp_cond_t * jmp_cond) const
{
  (void)jmp_cond;
  pc.increment();
}

void resolver_t::visit(const loop::btm_t * btm) const
{
  (void)btm;
  pc.increment();
}

void resolver_t::visit(const loop::lps_t * lps) const
{
  (void)lps;
  pc.increment();
}

void resolver_t::visit(const end::end_t * end) const
{
  (void)end;
  pc.increment();
}

void resolver_t::visit(const end::endi_t * endi) const
{
  (void)endi;
  pc.increment();
}

void resolver_t::visit(const nop::nop_t * nop) const
{
  (void)nop;
  pc.increment();
}

void resolver_t::visit(const assign_t * assign) const
{
  (void)assign;
}

void resolver_t::visit(const label_t * label) const
{
  if (variables.contains(label->name.lexeme)) {
    throw std::runtime_error("label redefinition is not allowed");
  } else {
    variables.insert({label->name.lexeme, pc.value});
  }
}

}

}
