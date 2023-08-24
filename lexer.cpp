#include <string_view>
#include <functional>
#include <cstdint>
#include <optional>

#include "token.hpp"
#include "num.hpp"
#include "lexer.hpp"
#include "keyword.hpp"
#include "error.hpp"

namespace dsp {

template <typename N>
constexpr static N parse_digit(const char c)
{
  switch (c) {
  default: [[fallthrough]];
  case '0': return 0;
  case '1': return 1;
  case '2': return 2;
  case '3': return 3;
  case '4': return 4;
  case '5': return 5;
  case '6': return 6;
  case '7': return 7;
  case '8': return 8;
  case '9': return 9;
  case 'a': return 10;
  case 'b': return 11;
  case 'c': return 12;
  case 'd': return 13;
  case 'e': return 14;
  case 'f': return 15;
  case 'A': return 10;
  case 'B': return 11;
  case 'C': return 12;
  case 'D': return 13;
  case 'E': return 14;
  case 'F': return 15;
  }
}

template <typename N, int base>
constexpr static N parse_number(const std::string_view s)
{
  N n = 0;
  for (std::string_view::size_type ix = 0; ix < s.length(); ix++) {
    n *= base;
    n += parse_digit<N>(s[ix]);
  }

  return n;
}

struct bin_t {
  constexpr static bool pred(const char c)
  {
    return c >= '0' && c <= '1';
  }

  template <typename N>
  constexpr static N parse(const std::string_view s)
  {
    return parse_number<N, 2>(s);
  }
};

struct dec_t {
  constexpr static bool pred(const char c)
  {
    return c >= '0' && c <= '9';
  }

  template <typename N>
  constexpr static N parse(const std::string_view s)
  {
    return parse_number<N, 10>(s);
  }
};

struct hex_t {
  constexpr static bool pred(const char c)
  {
    return dec_t::pred(c)
      || (c >= 'a' && c <= 'f')
      || (c >= 'A' && c <= 'F');
  }

  template <typename N>
  constexpr static N parse(const std::string_view s)
  {
    return parse_number<N, 16>(s);
  }
};

inline constexpr bool alpha_p(const char c)
{
  return (c >= 'a' && c <= 'z')
    || (c >= 'A' && c <= 'Z');
}

inline constexpr bool alpha_numeric_p(const char c)
{
  return alpha_p(c) || dec_t::pred(c) || (c == '_');
}

bool lexer_t::at_end_p()
{
  return current_ix >= source.length();
}

char lexer_t::peek()
{
  if (at_end_p()) return '\0';
  return source[current_ix];
}

bool lexer_t::match(const char expected)
{
  if (at_end_p()) return false;
  else if (source[current_ix] != expected) return false;
  pos.col++;
  current_ix++;
  return true;
}

char lexer_t::advance()
{
  pos.col++;
  return source[current_ix++];
}

const std::string_view lexer_t::lexeme()
{
  return source.substr(start_ix, current_ix - start_ix);
}

template <typename T>
token_t lexer_t::_number()
{
  while (T::pred(peek())) advance();

  return {pos, token_t::number, lexeme(), T::template parse<num_t>(lexeme())};
}

token_t lexer_t::_identifier()
{
  while (alpha_numeric_p(peek())) advance();
  std::optional<enum token_t::type_t> keyword = keyword::find(lexeme());
  if (keyword) return {pos, *keyword, lexeme()};
  else         return {pos, token_t::identifier, lexeme()};
}

std::optional<token_t> lexer_t::lex_token()
{
  using enum token_t::type_t;

  while (true) {
    if (at_end_p())
      return {{pos, eof, ""}};

    start_ix = current_ix;

    const char c = advance();
    switch (c) {
    case '(': return {{pos, left_paren, lexeme()}};
    case ')': return {{pos, right_paren, lexeme()}};
    case ',': return {{pos, comma, lexeme()}};
    case '.': return {{pos, dot, lexeme()}};
    case '+': return {{pos, plus, lexeme()}};
    case '-': return {{pos, minus, lexeme()}};
    case '*': return {{pos, star, lexeme()}};
    case '/': return {{pos, slash, lexeme()}};
    case '~': return {{pos, tilde, lexeme()}};
    case '&': return {{pos, ampersand, lexeme()}};
    case '|': return {{pos, bar, lexeme()}};
    case '^': return {{pos, carot, lexeme()}};
    case '=': return {{pos, equal, lexeme()}};
    case ':': return {{pos, colon, lexeme()}};
    case '#': return {{pos, hash, lexeme()}};
    case '<':
      if (match('<')) return {{pos, left_shift, lexeme()}};
      break;
    case '>':
      if (match('>')) return {{pos, right_shift, lexeme()}};
      break;
    case ';':
      while (!at_end_p() && peek() != '\n') advance();
      break;
    case '\\':
      if      (match('\n')) { continue; }
      else if (match('\r')) { if (match('\n')) continue; }
      break;
    case '\r':
    case ' ':
    case '\t':
      break;
    case '\n':
      {
	token_pos_t tmp = pos;
	pos.line++;
	pos.col = 0;
	return {{tmp, eol, lexeme()}};
      }
      break;
    case '%':
      if (bin_t::pred(peek())) {
	start_ix += 1;
	return {_number<bin_t>()};
      } else {
        return {{pos, percent, lexeme()}};
      }
    case '$':
      if (hex_t::pred(peek())) {
	start_ix += 1;
	return {_number<hex_t>()};
      }
      [[fallthrough]];
    case '0':
      if (match('x')) {
	if (hex_t::pred(peek())) {
	  start_ix += 2;
	  return {_number<hex_t>()};
	} else {
          error(pos.line, pos.col, "expected hexadecimal literal");
          return {};
        }
      } else if (match('b')) {
	if (bin_t::pred(peek())) {
	  start_ix += 2;
	  return {_number<bin_t>()};
	} else {
          error(pos.line, pos.col, "expected binary literal");
          return {};
        }
      }
      [[fallthrough]];
    default:
      if (dec_t::pred(c)) {
	return {_number<dec_t>()};
      } else if (alpha_p(c)) {
	return {_identifier()};
      } else {
	error(pos.line, pos.col - 1, "unexpected character");
	return {};
      }
      break;
    }
  }
  __builtin_unreachable();
}

std::vector<token_t> lexer_t::lex_tokens()
{
  std::vector<token_t> tokens;

  while (true) {
    std::optional<token_t> token_o = lex_token();
    if (!token_o) continue;
    tokens.push_back(*token_o);
    if (token_o->type == token_t::eof) break;
  }
  return tokens;
}

}
