#include "ast_printer.hpp"
#include "stmt_string.hpp"
#include "control_word.hpp"

namespace dsp {

namespace ast {

void printer_t::visit(const binary_t * binary) const
{
  parenthesize((binary->oper).lexeme, binary->left, binary->right);
}

void printer_t::visit(const grouping_t * grouping) const
{
  parenthesize("grouping", grouping->expr);
}

void printer_t::visit(const identifier_t * identifier) const
{
  parenthesize("identifier", identifier->name.lexeme);
}

void printer_t::visit(const literal_t * literal) const
{
  os << "0x" << std::hex << literal->value;
}

void printer_t::visit(const unary_t * unary) const
{
  parenthesize((unary->oper).lexeme, unary->right);
}

void printer_t::parenthesize(const std::string_view s, const expr_t * a) const
{
  os << '(' << s << ' ';
  a->accept(this);
  os << ')';
}

void printer_t::parenthesize(const std::string_view s1, const std::string_view s2, const expr_t * a) const
{
  os << '(' << s1 << ' ' << s2 << ' ';
  a->accept(this);
  os << ')';
}

void printer_t::parenthesize(const std::string_view s1, const std::string_view s2, const std::string_view s3, const expr_t * a) const
{
  os << '(' << s1 << ' ' << s2 << ' ' << s3 << ' ';
  a->accept(this);
  os << ')';
}

void printer_t::parenthesize(const std::string_view s1, const expr_t * a, const std::string_view s2) const
{
  os << '(' << s1 << ' ';
  a->accept(this);
  os << ' ' << s2 << ')';
}

void printer_t::parenthesize(const std::string_view s1, const expr_t * a, const std::string_view s2, const std::string_view s3) const
{
  os << '(' << s1 << ' ';
  a->accept(this);
  os << ' ' << s2 << ' ' << s3 << ')';
}

void printer_t::parenthesize(const std::string_view s) const
{
  os << '(' << s << ')';
}

void printer_t::parenthesize(const std::string_view s1, const std::string_view s2) const
{
  os << '(' << s1 << ' ' << s2 << ')';
}

void printer_t::parenthesize(const std::string_view s1, const std::string_view s2, const std::string_view s3) const
{
  os << '(' << s1 << ' ' << s2 << ' ' << s3 << ')';
}

void printer_t::parenthesize(const std::string_view s1, const std::string_view s2, const std::string_view s3, const std::string_view s4) const
{
  os << '(' << s1 << ' ' << s2 << ' ' << s3 << ' ' << s4 << ')';
}

void printer_t::parenthesize(const std::string_view s, const expr_t * a, const expr_t * b) const
{
  os << '(' << s << ' ';
  a->accept(this);
  os << ' ';
  b->accept(this);
  os << ')';
}

// instructions

enum {
  type_alu    = (0),
  type_x_bus  = (1),
  type_y_bus  = (2),
  type_d1_bus = (3),
};

//           111111111122222222223333333333444444444455555555556
// 0123456789012345678901234567890123456789012345678901234567890
// ad2   mov mc0,x  mov mul,p   mov mc1,y  mov alu,a   mov 0,ct1

void printer_t::insert_indent(int current_type) const
{
  constexpr int indents[4] = {
    [0] = 0,
    [1] = 6,
    [2] = 29,
    [3] = 52,
  };
  int desired_indent = indents[current_type];
  int current_indent = os.tellp();

  int indent = desired_indent - current_indent;
  if (indent > 0) {
    for (int i = 0; i < indent; i++) {
      os << ' ';
    }
  }
}

void printer_t::visit(const op::andl_t * andl) const
{
  (void)andl;
  os << "and";
}

void printer_t::visit(const op::orl_t * orl) const
{
  (void)orl;
  os << "or";
}

void printer_t::visit(const op::xorl_t * xorl) const
{
  (void)xorl;
  os << "xor";
}

void printer_t::visit(const op::add_t * add) const
{
  (void)add;
  os << "add";
}

void printer_t::visit(const op::sub_t * sub) const
{
  (void)sub;
  os << "sub";
}

void printer_t::visit(const op::ad2_t * ad2) const
{
  (void)ad2;
  os << "ad2";
}

void printer_t::visit(const op::sr_t * sr) const
{
  (void)sr;
  os << "sr";
}

void printer_t::visit(const op::rr_t * rr) const
{
  (void)rr;
  os << "rr";
}

void printer_t::visit(const op::sl_t * sl) const
{
  (void)sl;
  os << "sl";
}

void printer_t::visit(const op::rl_t * rl) const
{
  (void)rl;
  os << "rl";
}

void printer_t::visit(const op::rl8_t * rl8) const
{
  (void)rl8;
  os << "rl8";
}

void printer_t::visit(const op::mov_ram_x_t * mov_ram_x) const
{
  insert_indent(type_x_bus);
  os << "mov"
     << ' '
     << op::x_src_string[static_cast<int>(mov_ram_x->src.value)]
     << ",x";
}

void printer_t::visit(const op::mov_mul_p_t * mov_mul_p) const
{
  insert_indent(type_x_bus);
  (void)mov_mul_p;
  os << "mov mul,p";
}

void printer_t::visit(const op::mov_ram_p_t * mov_ram_p) const
{
  insert_indent(type_x_bus);
  os << "mov"
     << ' '
     << op::x_src_string[static_cast<int>(mov_ram_p->src.value)]
     << ",p";
}

void printer_t::visit(const op::mov_ram_y_t * mov_ram_y) const
{
  insert_indent(type_y_bus);
  os << "mov"
     << ' '
     << op::y_src_string[static_cast<int>(mov_ram_y->src.value)]
     << ",y";
}

void printer_t::visit(const op::clr_a_t * clr_a) const
{
  insert_indent(type_y_bus);
  (void)clr_a;
  os << "clr a";
}

void printer_t::visit(const op::mov_alu_a_t * mov_alu_a) const
{
  insert_indent(type_y_bus);
  (void)mov_alu_a;
  os << "mov alu,a";
}

void printer_t::visit(const op::mov_ram_a_t * mov_ram_a) const
{
  insert_indent(type_y_bus);
  os << "mov"
     << ' '
     << op::y_src_string[static_cast<int>(mov_ram_a->src.value)]
     << ",a";
}

void printer_t::visit(const op::mov_imm_d1_t * mov_imm_d1) const
{
  insert_indent(type_d1_bus);
  os << "mov"
     << ' ';
  mov_imm_d1->imm.expr->accept(this);
  os << ','
     << op::d1_dst_string[static_cast<int>(mov_imm_d1->dst.value)];
}

void printer_t::visit(const op::mov_ram_d1_t * mov_ram_d1) const
{
  insert_indent(type_d1_bus);
  os << "mov"
     << ' '
     << op::d1_src_string[static_cast<int>(mov_ram_d1->src.value)]
     << ','
     << op::d1_dst_string[static_cast<int>(mov_ram_d1->dst.value)];
}

void printer_t::visit(const op::control_word_t * control_word) const
{
  for (decltype(control_word->ops)::size_type ix = 0; ix < control_word->ops.size(); ix++) {
    const auto& op = control_word->ops[ix];
    std::visit([*this](auto&& arg){ (arg).accept(this); }, op);
    if (ix < (control_word->ops.size() - 1))
      os << "  ";
  }
}

void printer_t::visit(const load::mvi_t * mvi) const
{
  os << "mvi"
     << ' ';
  mvi->imm.expr->accept(this);
  os << ','
     << load::dst_string[static_cast<int>(mvi->dst.value)];
}

void printer_t::visit(const load::mvi_cond_t * mvi_cond) const
{
  os << "mvi"
     << ' ';
  mvi_cond->imm.expr->accept(this);
  os << ','
     << load::dst_string[static_cast<int>(mvi_cond->dst.value)]
     << load::cond_string[static_cast<int>(mvi_cond->cond.value)];
}

static std::string dma_hold_add(dma::hold_t hold, dma::add_t add)
{
  return dma::hold_mode_string[static_cast<int>(hold.value)]
       + dma::add_mode_string[static_cast<int>(add.value)];
}

void printer_t::visit(const dma::src_d0_imm_t * src_d0_imm) const
{
  os << dma_hold_add(src_d0_imm->hold, src_d0_imm->add)
     << ' '
     << dma::src_string[static_cast<int>(src_d0_imm->src.value)]
     << ','
     << "d0"
     << ',';
  src_d0_imm->imm.expr->accept(this);
}

void printer_t::visit(const dma::d0_dst_imm_t * d0_dst_imm) const
{
  os << dma_hold_add(d0_dst_imm->hold, d0_dst_imm->add)
     << ' '
     << "d0"
     << ','
     << dma::dst_string[static_cast<int>(d0_dst_imm->dst.value)]
     << ',';
  d0_dst_imm->imm.expr->accept(this);
}

void printer_t::visit(const dma::src_d0_ram_t * src_d0_ram) const
{
  os << dma_hold_add(src_d0_ram->hold, src_d0_ram->add)
     << ' '
     << dma::src_string[static_cast<int>(src_d0_ram->src.value)]
     << ','
     << "d0"
     << ','
     << dma::length_ram_string[static_cast<int>(src_d0_ram->ram.value)];
}

void printer_t::visit(const dma::d0_dst_ram_t * d0_dst_ram) const
{
  os << dma_hold_add(d0_dst_ram->hold, d0_dst_ram->add)
     << ' '
     << "d0"
     << ','
     << dma::dst_string[static_cast<int>(d0_dst_ram->dst.value)]
     << ','
     << dma::length_ram_string[static_cast<int>(d0_dst_ram->ram.value)];
}

void printer_t::visit(const jump::jmp_t * jmp) const
{
  os << "jmp"
     << ' ';
  jmp->imm.expr->accept(this);
}

void printer_t::visit(const jump::jmp_cond_t * jmp_cond) const
{
  os << "jmp"
     << ' '
     << jump::cond_string[static_cast<int>(jmp_cond->cond.value)]
     << ',';
  jmp_cond->imm.expr->accept(this);
}

void printer_t::visit(const loop::btm_t * btm) const
{
  (void)btm;
  os << "btm";
}

void printer_t::visit(const loop::lps_t * lps) const
{
  (void)lps;
  os << "lps";
}

void printer_t::visit(const end::end_t * end) const
{
  (void)end;
  os << "end";
}

void printer_t::visit(const end::endi_t * endi) const
{
  (void)endi;
  os << "endi";
}

void printer_t::visit(const nop::nop_t * nop) const
{
  (void)nop;
  os << "nop";
}

void printer_t::visit(const assign_t * assign) const
{
  parenthesize("assign", assign->name.lexeme, assign->value);
}

void printer_t::visit(const label_t * label) const
{
  parenthesize("label", label->name.lexeme);
}

}

}
