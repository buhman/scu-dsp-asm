/*
expression     → term ;
term           → factor ( ( "-" | "+" ) factor )* ;
factor         → unary ( ( "/" | "*" | "%" ) unary )* ;
unary          → ( "~" | "+" | "-" ) unary
               | shift ;
shift          → andl ( ( "<<" | ">>" ) andl )*
andl           → orl ( "&" orl )*
orl            → andl ( ( "|" | "^" ) andl )*
primary        → NUMBER
               | "(" expression ")" ;
*/

#include <string>

#include "parser.hpp"
#include "num.hpp"
#include "error.hpp"

namespace dsp {

using enum token_t::type_t;

bool parser_t::at_end_p()
{
  return peek().type == eof;
}

parse_error_t parser_t::error(const token_t& token, const std::string message)
{
  dsp::error(token, message);
  return parse_error_t(message);
}

token_t& parser_t::previous()
{
  return tokens[current_ix-1];
}

token_t& parser_t::peek()
{
  return tokens[current_ix];
}

token_t& parser_t::advance()
{
  if (!at_end_p()) current_ix++;
  return previous();
}

bool parser_t::check(enum token_t::type_t token_type)
{
  if (at_end_p()) return false;
  return peek().type == token_type;
}

bool parser_t::match(enum token_t::type_t token_type)
{
  if (check(token_type)) {
    advance();
    return true;
  }
  return false;
}

template <typename... Targs>
bool parser_t::match(enum token_t::type_t token_type, Targs... args)
{
  return match(token_type) || match(args...);
}

token_t parser_t::consume(enum token_t::type_t token_type, const std::string error_message)
{
  if (check(token_type)) return advance();

  throw error(peek(), error_message);
}

expr_t * parser_t::expression()
{
  return term();
}

expr_t * parser_t::term()
{
  expr_t * left = factor();
  while (match(minus, plus)) {
    token_t oper = previous();
    expr_t * right = factor();
    left = new binary_t(left, oper, right);
  }
  return left;
}

expr_t * parser_t::factor()
{
  expr_t * left = unary();
  while (match(slash, star, percent)) {
    token_t oper = previous();
    expr_t * right = unary();
    left = new binary_t(left, oper, right);
  }
  return left;
}

expr_t * parser_t::unary()
{
  if (match(tilde, plus, minus)) {
    token_t oper = previous();
    expr_t * right = unary();
    return new unary_t(oper, right);
  }
  return shift();
}

expr_t * parser_t::shift()
{
  expr_t * left = andl();
  while (match(left_shift, right_shift)) {
    token_t oper = previous();
    expr_t * right = andl();
    left = new binary_t(left, oper, right);
  }
  return left;
}

expr_t * parser_t::andl()
{
  expr_t * left = orl();
  while (match(ampersand)) {
    token_t oper = previous();
    expr_t * right = orl();
    left = new binary_t(left, oper, right);
  }
  return left;
}

expr_t * parser_t::orl()
{
  expr_t * left = primary();
  while (match(bar, carot)) {
    token_t oper = previous();
    expr_t * right = primary();
    left = new binary_t(left, oper, right);
  }
  return left;
}

expr_t * parser_t::primary()
{
  if (match(number)) return new literal_t(std::get<num_t>(previous().literal));

  if (match(left_paren)) {
    expr_t * expr = expression();
    consume(right_paren, "expected ')' after expression.");
    return new grouping_t(expr);
  }

  throw error(peek(), "expected expression");
}

/*
void parser_t::synchronize()
{
  advance();
  while (!at_end_p()) {
    if (previous().type == eol) return;
    advance();
  }
}
*/

}
