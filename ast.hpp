#pragma once

#include <ostream>
#include <string_view>

#include "visitor.hpp"
#include "expr.hpp"
#include "num.hpp"

namespace dsp {

struct ast_printer_t : visitor_t<void>
{
  ast_printer_t(std::ostream& os)
    : os(os) {}

  std::ostream& os;

  void visit(const unary_t * unary) const;
  void visit(const binary_t * binary) const;
  void visit(const grouping_t * grouping) const;
  void visit(const literal_t * literal) const;

  void parenthesize(const std::string_view s, const expr_t * a) const;
  void parenthesize(const std::string_view s, const expr_t * a, const expr_t * b) const;
};

}