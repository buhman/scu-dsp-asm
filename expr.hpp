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

struct assign_t : expr_accept_t<assign_t>
{
  assign_t(token_t& name, expr_t& value)
    : name(name), value(value) {}

  const token_t name;
  const expr_t& value;
};

struct literal_t : expr_accept_t<literal_t>
{
  literal_t(num_t value)
    : value(value) {}

  const num_t value;
};

}
