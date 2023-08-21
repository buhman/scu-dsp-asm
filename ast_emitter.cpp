#include <unordered_map>

#include "ast_emitter.hpp"

namespace dsp {

namespace ast {

// expressions

uint32_t emitter_t::visit(const binary_t * binary) const
{
  uint32_t l = binary->left->accept(this);
  uint32_t r = binary->right->accept(this);

  using enum dsp::token_t::type_t;

  switch (binary->oper.type) {
  case plus:         return l + r; // add
  case minus:        return l - r; // subtract
  case star:         return l * r; // multiply
  case slash:        return l / r; // divide
  case percent:      return l % r; // modulus
  case ampersand:    return l & r; // logical and
  case bar:          return l | r; // logical or
  case carot:        return l ^ r; // logical xor
  case left_shift:   return l << r; // logical left shift
  case right_shift:  return l >> r; // logical right shift
  default:
    throw std::runtime_error("invalid binary operand");
  }
}

uint32_t emitter_t::visit(const grouping_t * grouping) const
{
  return grouping->expr->accept(this);
}

uint32_t emitter_t::visit(const identifier_t * identifier) const
{
  if (variables.contains(identifier->name.lexeme)) {
    return variables.at(identifier->name.lexeme);
  } else {
    throw std::runtime_error("undefined identifier");
  }
}

uint32_t emitter_t::visit(const literal_t * literal) const
{
  return literal->value;
}

uint32_t emitter_t::visit(const unary_t * unary) const
{
  uint32_t r = unary->right->accept(this);

  using enum dsp::token_t::type_t;

  switch (unary->oper.type) {
  case tilde:  return ~r;
  case plus:   return +r;
  case minus:  return -r;
  default:
    throw std::runtime_error("invalid binary operand");
  }
}

// instructions

uint32_t emitter_t::visit(const op::alu_t * alu) const
{
  return alu->code() | alu->bits();
}

uint32_t emitter_t::visit(const op::mov_ram_x_t * mov_ram_x) const
{
  return mov_ram_x->code() | mov_ram_x->bits();
}

uint32_t emitter_t::visit(const op::mov_mul_p_t * mov_mul_p) const
{
  return mov_mul_p->code() | mov_mul_p->bits();
}

uint32_t emitter_t::visit(const op::mov_ram_p_t * mov_ram_p) const
{
  return mov_ram_p->code() | mov_ram_p->bits();
}

uint32_t emitter_t::visit(const op::mov_ram_y_t * mov_ram_y) const
{
  return mov_ram_y->code() | mov_ram_y->bits();
}

uint32_t emitter_t::visit(const op::clr_a_t * clr_a) const
{
  return clr_a->code() | clr_a->bits();
}

uint32_t emitter_t::visit(const op::mov_alu_a_t * mov_alu_a) const
{
  return mov_alu_a->code() | mov_alu_a->bits();
}

uint32_t emitter_t::visit(const op::mov_ram_a_t * mov_ram_a) const
{
  return mov_ram_a->code() | mov_ram_a->bits();
}

uint32_t emitter_t::visit(const op::mov_imm_d1_t * mov_imm_d1) const
{
  num_t value = mov_imm_d1->imm.expr->accept(this);
  if (mov_imm_d1->imm.in_range(value))
    return mov_imm_d1->code() | mov_imm_d1->bits() | value;
  else
    throw std::runtime_error("out of range");
}

uint32_t emitter_t::visit(const op::mov_ram_d1_t * mov_ram_d1) const
{
  return mov_ram_d1->code() | mov_ram_d1->bits();
}

uint32_t emitter_t::visit(const op::control_word_t * control_word) const
{
  uint32_t word = 0;
  for (auto& op : control_word->ops) { word |= dynamic_cast<const stmt_t *>(op)->accept(this); }
  return word;
}

uint32_t emitter_t::visit(const load::mvi_t * mvi) const
{
  return mvi->code() | mvi->bits();
}

uint32_t emitter_t::visit(const load::mvi_cond_t * mvi_cond) const
{
  return mvi_cond->code() | mvi_cond->bits();
}

uint32_t emitter_t::visit(const dma::src_d0_imm_t * src_d0_imm) const
{
  num_t value = src_d0_imm->imm.expr->accept(this);
  if (src_d0_imm->imm.in_range(value))
    return src_d0_imm->code() | src_d0_imm->bits() | value;
  else
    throw std::runtime_error("out of range");
}

uint32_t emitter_t::visit(const dma::d0_dst_imm_t * d0_dst_imm) const
{
  num_t value = d0_dst_imm->imm.expr->accept(this);
  if (d0_dst_imm->imm.in_range(value))
    return d0_dst_imm->code() | d0_dst_imm->bits() | value;
  else
    throw std::runtime_error("out of range");
}

uint32_t emitter_t::visit(const dma::src_d0_ram_t * src_d0_ram) const
{
  return src_d0_ram->code() | src_d0_ram->bits();
}

uint32_t emitter_t::visit(const dma::d0_dst_ram_t * d0_dst_ram) const
{
  return d0_dst_ram->code() | d0_dst_ram->bits();
}

uint32_t emitter_t::visit(const jump::jmp_t * jmp) const
{
  return jmp->code() | jmp->bits();
}

uint32_t emitter_t::visit(const jump::jmp_cond_t * jmp_cond) const
{
  return jmp_cond->code() | jmp_cond->bits();
}

uint32_t emitter_t::visit(const loop::btm_t * btm) const
{
  return btm->code() | btm->bits();
}

uint32_t emitter_t::visit(const loop::lps_t * lps) const
{
  return lps->code() | lps->bits();
}

uint32_t emitter_t::visit(const end::end_t * end) const
{
  return end->code() | end->bits();
}

uint32_t emitter_t::visit(const end::endi_t * endi) const
{
  return endi->code() | endi->bits();
}

uint32_t emitter_t::visit(const nop::nop_t * nop) const
{
  return nop->code() | nop->bits();
}

uint32_t emitter_t::visit(const assign_t * assign) const
{
  if (variables.contains(assign->name.lexeme)) {
    throw std::runtime_error("assignment redefinition is not allowed");
  } else {
    num_t value = assign->value->accept(this);
    variables.insert({assign->name.lexeme, value});
  }
  return 0xffff'ffff; // lazy hack
}

uint32_t emitter_t::visit(const label_t * label) const
{
  (void)label;
  return 0xffff'ffff; // lazy hack
}

}

}
