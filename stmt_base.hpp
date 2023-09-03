#pragma once

#include "visitor.hpp"

namespace dsp {

struct stmt_t
{
  virtual void accept(visitor_t<void> const * visitor) const = 0;
  virtual uint32_t accept(visitor_t<uint32_t> const * visitor) const = 0;
};

template <typename T>
struct stmt_accept_t : stmt_t {
    virtual void accept(visitor_t<void> const * visitor) const {
      return visitor->visit(static_cast<const T*>(this));
    }

    virtual uint32_t accept(visitor_t<uint32_t> const * visitor) const
    {
      return visitor->visit(static_cast<const T*>(this));
    }
};

}
