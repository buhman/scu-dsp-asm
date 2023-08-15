#include "ast.hpp"

namespace dsp {

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

void ast_printer_t::visit(const literal_t * literal) const
{
  os << std::to_string(literal->value);
}

void ast_printer_t::visit(const assign_t * expr) const
{
  parenthesize((expr->name).lexeme, &(expr->value));
}

}
