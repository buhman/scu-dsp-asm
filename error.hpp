#pragma once

#include <iostream>
#include <string>

namespace dsp {

extern bool had_error;

static inline void report(const int line, const int col, const std::string where, const std::string message)
{
  std::cerr << "[line " << line
            << " col " << col
            << "] error" << where << ": " << message
            << std::endl;

  had_error = true;
}

static inline void error(const int line,  const int col, std::string message)
{
  report(line, col, "", message);
}

static inline void error(const token_t& token, const std::string message)
{
  using enum token_t::type_t;

  if (token.type == eof) {
    report(token.pos.line, token.pos.col, " at end", message);
  } else {
    report(token.pos.line, token.pos.col, " at '" + std::string(token.lexeme) + "'", message);
  }
}

}
