#pragma once

#include <string>

#include "token.hpp"
#include "visitor.hpp"
#include "num.hpp"

namespace dsp {

struct expr_t
{
  virtual void accept(visitor_t<void> const * visitor) const = 0;
  virtual std::string accept(visitor_t<std::string> const * visitor) const = 0;
};

template <typename T>
struct expr_accept_t : expr_t {
    virtual void accept(visitor_t<void> const * visitor) const {
      return visitor->visit(static_cast<const T*>(this));
    }

    virtual std::string accept(visitor_t<std::string> const * visitor) const
    {
      return visitor->visit(static_cast<const T*>(this));
    }
};

struct binary_t : expr_accept_t<binary_t>
{
  binary_t(expr_t * left, token_t oper, expr_t * right)
    : left(left), oper(oper), right(right) {}

  const expr_t * left;
  const token_t oper;
  const expr_t * right;
};

struct grouping_t : expr_accept_t<grouping_t>
{
  grouping_t(expr_t * expr)
    : expr(expr) {}

  const expr_t * expr;
};

struct identifier_t : expr_accept_t<identifier_t>
{
  identifier_t(token_t name)
    : name(name) {}

  const token_t name;
};

struct literal_t : expr_accept_t<literal_t>
{
  literal_t(num_t value)
    : value(value) {}

  const num_t value;
};

struct unary_t : expr_accept_t<unary_t>
{
  unary_t(token_t oper, expr_t * right)
    : oper(oper), right(right) {}

  const token_t oper;
  const expr_t * right;
};

}
