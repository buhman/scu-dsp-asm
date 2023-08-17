#pragma once

#include <string_view>
#include <ostream>
#include <variant>

#include "num.hpp"

namespace dsp {

struct object_t {
};

struct token_pos_t {
  int line;
  int col;
};

struct token_t {
  using num_type = num_t;

  enum type_t {
    left_paren,
    right_paren,

    comma,
    dot,

    // operators
    plus,
    minus,
    star,
    slash,
    percent,
    tilde,
    ampersand,
    bar,
    carot,
    left_shift,
    right_shift,
    equal,

    // literals
    identifier,
    string,
    number,

    // ends
    eof,
    eol,

    // keywords
    #include "keyword.enum_inc"
  };

  using literal_t = std::variant<std::monostate, num_type>;

  const token_pos_t pos;
  const type_t type;
  const std::string_view lexeme;
  const literal_t literal;

  token_t() = delete;

  constexpr token_t(token_pos_t pos, type_t type, const std::string_view lexeme, num_type number)
    : pos(pos), type(type), lexeme(lexeme), literal(number)
  { }

  constexpr token_t(token_pos_t pos, type_t type, const std::string_view lexeme)
    : pos(pos), type(type), lexeme(lexeme), literal()
  { }

  friend std::ostream& operator<<(std::ostream& os, const enum token_t::type_t type)
  {
    switch (type) {
    case left_paren   : return os << "LEFT_PAREN";
    case right_paren  : return os << "RIGHT_PAREN";

    case comma        : return os << "COMMA";
    case dot          : return os << "DOT";

      // operators
    case plus         : return os << "PLUS";
    case minus        : return os << "MINUS";
    case star         : return os << "STAR";
    case slash        : return os << "SLASH";
    case percent      : return os << "PERCENT";
    case tilde        : return os << "TILDE";
    case ampersand    : return os << "AMPERSAND";
    case bar          : return os << "BAR";
    case carot        : return os << "CAROT";
    case left_shift   : return os << "LEFT_SHIFT";
    case right_shift  : return os << "RIGHT_SHIFT";
    case equal        : return os << "EQUAL";

      // literals
    case identifier   : return os << "IDENTIFIER";
    case string       : return os << "STRING";
    case number       : return os << "NUMBER";

    // keywords
    #include "keyword.case_inc"

    case eof          : return os << "EOF";
    case eol          : return os << "EOL";
    }
    __builtin_unreachable();
  }

  friend std::ostream& operator<<(std::ostream& os, const token_t& token)
  {
    os << token.type << ' ' << token.lexeme;

    if (auto* v = std::get_if<num_type>(&token.literal)) {
      os << '/' << *v;
    } else { // std::monostate
    }

    return os;
  }

};

}
