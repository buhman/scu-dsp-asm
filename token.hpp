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

    // keywords
    _alh,
    _all,
    _alu,
    _m0,
    _m1,
    _m2,
    _m3,
    _mc0,
    _mc1,
    _mc2,
    _mc3,
    _mul,
    _nop,
    _and,
    _or,
    _xor,
    _add,
    _sub,
    _ad2,
    _sr,
    _rr,
    _sl,
    _rl,
    _rl8,
    _clr,
    _mov,
    _mvi,
    _dma,
    _dmah,
    _jmp,
    _btm,
    _lps,
    _end,
    _endi,
    _equ,
    _org,
    _ends,

    eof,
    eol,
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
    case _alh         : return os << "ALH";
    case _all         : return os << "ALL";
    case _alu         : return os << "ALU";
    case _m0          : return os << "M0";
    case _m1          : return os << "M1";
    case _m2          : return os << "M2";
    case _m3          : return os << "M3";
    case _mc0         : return os << "MC0";
    case _mc1         : return os << "MC1";
    case _mc2         : return os << "MC2";
    case _mc3         : return os << "MC3";
    case _mul         : return os << "MUL";
    case _nop         : return os << "NOP";
    case _and         : return os << "AND";
    case _or          : return os << "OR";
    case _xor         : return os << "XOR";
    case _add         : return os << "ADD";
    case _sub         : return os << "SUB";
    case _ad2         : return os << "AD2";
    case _sr          : return os << "SR";
    case _rr          : return os << "RR";
    case _sl          : return os << "SL";
    case _rl          : return os << "RL";
    case _rl8         : return os << "RL8";
    case _clr         : return os << "CLR";
    case _mov         : return os << "MOV";
    case _mvi         : return os << "MVI";
    case _dma         : return os << "DMA";
    case _dmah        : return os << "DMAH";
    case _jmp         : return os << "JMP";
    case _btm         : return os << "BTM";
    case _lps         : return os << "LPS";
    case _end         : return os << "END";
    case _endi        : return os << "ENDI";
    case _equ         : return os << "EQU";
    case _org         : return os << "ORG";
    case _ends        : return os << "ENDS";

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
