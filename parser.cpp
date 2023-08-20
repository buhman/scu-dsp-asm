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
#include <optional>
#include <cassert>

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
    consume(right_paren, "expected ')' after expression");
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

std::optional<op::op_t *> parser_t::alu()
{
  using namespace dsp::op;

  if      (match(_and)) return {new alu_t(alu_type_t::andl)};
  else if (match(_or )) return {new alu_t(alu_type_t::orl)};
  else if (match(_xor)) return {new alu_t(alu_type_t::xorl)};
  else if (match(_add)) return {new alu_t(alu_type_t::add)};
  else if (match(_sub)) return {new alu_t(alu_type_t::sub)};
  else if (match(_ad2)) return {new alu_t(alu_type_t::ad2)};
  else if (match(_sr )) return {new alu_t(alu_type_t::sr)};
  else if (match(_rr )) return {new alu_t(alu_type_t::rr)};
  else if (match(_sl )) return {new alu_t(alu_type_t::sl)};
  else if (match(_rl )) return {new alu_t(alu_type_t::rl)};
  else if (match(_rl8)) return {new alu_t(alu_type_t::rl8)};
  else                  return {};
}

bool parser_t::xyd1_src()
{
  const bool mc = match(_mc0) || match(_mc1) || match(_mc2) || match(_mc3);
  const bool m  = match(_m0 ) || match(_m1 ) || match(_m2 ) || match(_m3 );
  const bool al = match(_alh) || match(_all);
  return mc || m || al;
}

static op::xy_src_t xy_src(const token_t& token)
{
  using namespace dsp::op;

  switch (token.type) {
  case _mc0: return xy_src_t::mc0;
  case _mc1: return xy_src_t::mc1;
  case _mc2: return xy_src_t::mc2;
  case _mc3: return xy_src_t::mc3;
  case _m0:  return xy_src_t::m0;
  case _m1:  return xy_src_t::m1;
  case _m2:  return xy_src_t::m2;
  case _m3:  return xy_src_t::m3;
  default: assert(false); __builtin_unreachable();
  }
}

static op::d1_src_t d1_src(const token_t& token)
{
  using namespace dsp::op;

  switch (token.type) {
  case _mc0: return d1_src_t::mc0;
  case _mc1: return d1_src_t::mc1;
  case _mc2: return d1_src_t::mc2;
  case _mc3: return d1_src_t::mc3;
  case _m0:  return d1_src_t::m0;
  case _m1:  return d1_src_t::m1;
  case _m2:  return d1_src_t::m2;
  case _m3:  return d1_src_t::m3;
  case _alh: return d1_src_t::alh;
  case _all: return d1_src_t::all;
  default: assert(false); __builtin_unreachable();
  }
}

std::optional<op::d1_dest_t> parser_t::d1_dest()
{
  using namespace dsp::op;

  if      (match(_rx))  return {d1_dest_t::rx};
  else if (match(_pl))  return {d1_dest_t::pl};
  else if (match(_ra0)) return {d1_dest_t::ra0};
  else if (match(_wa0)) return {d1_dest_t::wa0};
  else if (match(_lop)) return {d1_dest_t::lop};
  else if (match(_top)) return {d1_dest_t::top};
  else if (match(_ct0)) return {d1_dest_t::ct0};
  else if (match(_ct1)) return {d1_dest_t::ct1};
  else if (match(_ct2)) return {d1_dest_t::ct2};
  else if (match(_ct3)) return {d1_dest_t::ct3};
  else                  return {};
}

std::optional<op::op_t *> parser_t::xyd1_bus()
{
  if (match(_mov)) {
    if (match(_alu)) {
      consume(comma, "expected `,` after `mov alu`");
      consume(_a, "expected `a` after `mov alu,`");
      return {new op::mov_alu_a_t()};
    } else if (match(_mul)) {
      consume(comma, "expected ',' after `mov mul`");
      consume(_p, "expected 'p' after `mov mul,`");
      return {new op::mov_mul_p_t()};
    } else if (xyd1_src()) {
      const token_t& src_token = previous();
      consume(comma, "expected `,` after mov src operand");
      // this is starting to feel a bit ugly...
      bool d1 = src_token.type == _alh || src_token.type == _alh;
      if      (!d1 && match(_y))        return {new op::mov_ram_y_t(xy_src(src_token))};
      else if (!d1 && match(_a))        return {new op::mov_ram_a_t(xy_src(src_token))};
      else if (!d1 && match(_x))        return {new op::mov_ram_x_t(xy_src(src_token))};
      else if (!d1 && match(_p))        return {new op::mov_ram_p_t(xy_src(src_token))};
      else if (auto dest_o = d1_dest()) return {new op::mov_ram_d1_t(d1_src(src_token), *dest_o)};
      else
	throw error(peek(), "expected x-bus, y-bus, or d-bus destination operand");
    } else {
      expr_t * expr = expression();
      simm_t<8> simm = simm_t<8>(expr);
      if (auto dest_o = d1_dest())
	return {new op::mov_imm_d1_t(simm, *dest_o)};
      else
      	throw error(peek(), "expected d1 destination operand");
    }
  } else if (match(_clr)) {
    consume(_a, "expected `a` after `clr`");
    return {new op::clr_a_t()};
  } else {
    return {};
  }
}

std::optional<stmt_t *> parser_t::op()
{
  std::vector<const op::op_t *> ops;
  while (true) {
    // fixme: check for emplacement here
    if      (auto stmt_o = alu()     ) ops.emplace_back(*stmt_o);
    else if (auto stmt_o = xyd1_bus()) ops.emplace_back(*stmt_o);
    else                        break;
  }
  if (ops.size() != 0)
    return {new op::instruction_t(ops)};
  else
    return {};
}

std::optional<stmt_t *> parser_t::instruction()
{
  // "nop"
  // op
  // load
  // dma
  // jump
  // loop
  // end
  return {};
}

std::optional<stmt_t *> parser_t::instruction_statement()
{
  // label
  // instruction
  // newline
  return {};
}

stmt_t * parser_t::statement()
{
  return nullptr;
}

}
