#pragma once

#include <string_view>
#include <optional>
#include <vector>

#include "token.hpp"

namespace dsp {

struct lexer_t {
  const std::string_view source;
  std::string_view::size_type start_ix;
  std::string_view::size_type current_ix;
  token_pos_t pos;

  lexer_t() = delete;

  constexpr lexer_t(const std::string_view source)
    : source(source), start_ix(0), current_ix(0), pos{ .line = 1, .col = 0 }
  { }

  std::optional<token_t> lex_token();
  std::vector<token_t> lex_tokens();

private:
  bool at_end_p();

  char peek();

  bool match(const char expected);

  char advance();

  const std::string_view lexeme();

  template <typename T>
  token_t _number();

  token_t _identifier();
};

}
