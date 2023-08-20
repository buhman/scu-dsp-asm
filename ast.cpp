#include "ast.hpp"
#include "stmt_string.hpp"

namespace dsp {

void ast_printer_t::visit(const unary_t * unary) const
{
  parenthesize((unary->oper).lexeme, unary->right);
}

void ast_printer_t::visit(const binary_t * binary) const
{
  parenthesize((binary->oper).lexeme, binary->left, binary->right);
}

void ast_printer_t::visit(const grouping_t * grouping) const
{
  parenthesize("grouping", grouping->expr);
}

void ast_printer_t::visit(const literal_t * literal) const
{
  os << std::to_string(literal->value);
}

void ast_printer_t::parenthesize(const std::string_view s, const expr_t * a) const
{
  os << '(' << s << ' ';
  a->accept(this);
  os << ')';
}

void ast_printer_t::parenthesize(const std::string_view s1, const std::string_view s2, const expr_t * a) const
{
  os << '(' << s1 << ' ' << s2 << ' ';
  a->accept(this);
  os << ')';
}

void ast_printer_t::parenthesize(const std::string_view s1, const std::string_view s2, const std::string_view s3, const expr_t * a) const
{
  os << '(' << s1 << ' ' << s2 << ' ' << s3 << ' ';
  a->accept(this);
  os << ')';
}

void ast_printer_t::parenthesize(const std::string_view s1, const expr_t * a, const std::string_view s2) const
{
  os << '(' << s1 << ' ';
  a->accept(this);
  os << ' ' << s2 << ')';
}

void ast_printer_t::parenthesize(const std::string_view s1, const expr_t * a, const std::string_view s2, const std::string_view s3) const
{
  os << '(' << s1 << ' ';
  a->accept(this);
  os << ' ' << s2 << ' ' << s3 << ')';
}

void ast_printer_t::parenthesize(const std::string_view s) const
{
  os << '(' << s << ')';
}

void ast_printer_t::parenthesize(const std::string_view s1, const std::string_view s2) const
{
  os << '(' << s1 << ' ' << s2 << ')';
}

void ast_printer_t::parenthesize(const std::string_view s1, const std::string_view s2, const std::string_view s3) const
{
  os << '(' << s1 << ' ' << s2 << ' ' << s3 << ')';
}

void ast_printer_t::parenthesize(const std::string_view s1, const std::string_view s2, const std::string_view s3, const std::string_view s4) const
{
  os << '(' << s1 << ' ' << s2 << ' ' << s3 << ' ' << s4 << ')';
}

void ast_printer_t::parenthesize(const std::string_view s, const expr_t * a, const expr_t * b) const
{
  os << '(' << s << ' ';
  a->accept(this);
  os << ' ';
  b->accept(this);
  os << ')';
}

// instructions

void ast_printer_t::visit(const op::alu_t * alu) const
{
  parenthesize(op::alu_type_string[static_cast<int>(alu->type)]);
}

void ast_printer_t::visit(const op::mov_ram_x_t * mov_ram_x) const
{
  parenthesize("mov", op::xy_src_string[static_cast<int>(mov_ram_x->src)], "x");
}

void ast_printer_t::visit(const op::mov_mul_p_t * mov_mul_p) const
{
  (void)mov_mul_p;
  parenthesize("mov mul p");
}

void ast_printer_t::visit(const op::mov_ram_p_t * mov_ram_p) const
{
  parenthesize("mov", op::xy_src_string[static_cast<int>(mov_ram_p->src)], "p");
}

void ast_printer_t::visit(const op::mov_ram_y_t * mov_ram_y) const
{
  parenthesize("mov", op::xy_src_string[static_cast<int>(mov_ram_y->src)], "y");
}

void ast_printer_t::visit(const op::clr_a_t * clr_a) const
{
  (void)clr_a;
  parenthesize("clr a");
}

void ast_printer_t::visit(const op::mov_alu_a_t * mov_alu_a) const
{
  (void)mov_alu_a;
  parenthesize("mov alu a");
}

void ast_printer_t::visit(const op::mov_ram_a_t * mov_ram_a) const
{
  parenthesize("mov", op::xy_src_string[static_cast<int>(mov_ram_a->src)], "a");
}

void ast_printer_t::visit(const op::mov_imm_d1_t * mov_imm_d1) const
{
  parenthesize("mov",
               mov_imm_d1->imm.expr,
               op::d1_dest_string[static_cast<int>(mov_imm_d1->dest)]);
}

void ast_printer_t::visit(const op::mov_ram_d1_t * mov_ram_d1) const
{
  parenthesize("mov",
               op::d1_src_string[static_cast<int>(mov_ram_d1->src)],
               op::d1_dest_string[static_cast<int>(mov_ram_d1->dest)]);
}

void ast_printer_t::visit(const op::control_word_t * control_word) const
{
  os << "(control_word ";
  for (const auto& op : control_word->ops) {
    reinterpret_cast<const stmt_t *>(op)->accept(this);
    os << ' ';
  }
  os << ')';
}

void ast_printer_t::visit(const load::mvi_t * mvi) const
{
  parenthesize("mvi", mvi->imm.expr, load::dest_string[static_cast<int>(mvi->dest)]);
}

void ast_printer_t::visit(const load::mvi_cond_t * mvi_cond) const
{
  parenthesize("mvi",
               mvi_cond->imm.expr,
               load::dest_string[static_cast<int>(mvi_cond->dest)],
               load::cond_string[static_cast<int>(mvi_cond->cond)]);
}

static std::string dma_hold_add(bool hold, dma::add_mode_t add)
{
  return dma::hold_mode_string[static_cast<int>(hold)]
       + dma::add_mode_string[static_cast<int>(add)];
}

void ast_printer_t::visit(const dma::src_d0_imm_t * src_d0_imm) const
{
  parenthesize(dma_hold_add(src_d0_imm->hold, src_d0_imm->add),
               dma::src_string[static_cast<int>(src_d0_imm->src)],
	       "d0",
               src_d0_imm->imm.expr);
}

void ast_printer_t::visit(const dma::d0_dst_imm_t * d0_dst_imm) const
{
  parenthesize(dma_hold_add(d0_dst_imm->hold, d0_dst_imm->add),
	       "d0",
               dma::dst_string[static_cast<int>(d0_dst_imm->dst)],
               d0_dst_imm->imm.expr);
}

void ast_printer_t::visit(const dma::src_d0_ram_t * src_d0_ram) const
{
  parenthesize(dma_hold_add(src_d0_ram->hold, src_d0_ram->add),
               dma::src_string[static_cast<int>(src_d0_ram->src)],
	       "d0",
               dma::length_ram_string[static_cast<int>(src_d0_ram->ram)]);
}

void ast_printer_t::visit(const dma::d0_dst_ram_t * d0_dst_ram) const
{
  parenthesize(dma_hold_add(d0_dst_ram->hold, d0_dst_ram->add),
	       "d0",
               dma::dst_string[static_cast<int>(d0_dst_ram->dst)],
               dma::length_ram_string[static_cast<int>(d0_dst_ram->ram)]);
}

void ast_printer_t::visit(const jump::jmp_t * jmp) const
{
  parenthesize("jmp", jmp->imm.expr);
}

void ast_printer_t::visit(const jump::jmp_cond_t * jmp_cond) const
{
  parenthesize("jmp",
	       jump::cond_string[static_cast<int>(jmp_cond->cond)],
	       jmp_cond->imm.expr);
}

void ast_printer_t::visit(const loop::btm_t * btm) const
{
  (void)btm;
  parenthesize("btm");
}

void ast_printer_t::visit(const loop::lps_t * lps) const
{
  (void)lps;
  parenthesize("lps");
}

void ast_printer_t::visit(const end::end_t * end) const
{
  (void)end;
  parenthesize("end");
}

void ast_printer_t::visit(const end::endi_t * endi) const
{
  (void)endi;
  parenthesize("endi");
}

void ast_printer_t::visit(const nop::nop_t * nop) const
{
  (void)nop;
  parenthesize("nop");
}

}
