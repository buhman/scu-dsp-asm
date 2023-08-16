#include <stdexcept>
#include <string>
#include <vector>

#include "token.hpp"
#include "expr.hpp"

namespace dsp {

struct parse_error_t : std::runtime_error
{
  parse_error_t(const std::string& msg)
    : std::runtime_error(msg)
  { }
};

struct parser_t
{
  int current_ix = 0;
  std::vector<token_t> tokens;

  parser_t(const std::vector<token_t>& tokens)
    : tokens(tokens)
  { }

  static parse_error_t error(const token_t& token, const std::string message);

  bool at_end_p();

  token_t& previous();
  token_t& peek();
  token_t& advance();
  bool check(enum token_t::type_t token_type);
  bool match(enum token_t::type_t token_type);
  template <typename... Targs>
  bool match(enum token_t::type_t token_type, Targs... args);
  token_t consume(enum token_t::type_t token_type, const std::string error_message);

  expr_t * expression();
  expr_t * term();
  expr_t * factor();
  expr_t * unary();
  expr_t * shift();
  expr_t * andl();
  expr_t * orl();
  expr_t * primary();

};

}
