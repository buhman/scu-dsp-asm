#include "ast.hpp"

namespace dsp {

void ast_printer_t::visit(const unary_t * unary) const
{
  parenthesize((unary->oper).lexeme, unary->expr);
}

void ast_printer_t::visit(const binary_t * binary) const
{
  parenthesize((binary->oper).lexeme, binary->left, binary->right);
}

void ast_printer_t::visit(const grouping_t * grouping) const
{
  parenthesize(std::string_view("<grouping>"), grouping->expr);
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

void ast_printer_t::parenthesize(const std::string_view s, const expr_t * a, const expr_t * b) const
{
  os << '(' << s << ' ';
  a->accept(this);
  os << ' ';
  b->accept(this);
  os << ')';
}

}
