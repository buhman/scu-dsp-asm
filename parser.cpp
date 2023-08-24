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

const token_t& parser_t::previous()
{
  return tokens[current_ix-1];
}

const token_t& parser_t::peek()
{
  return tokens[current_ix];
}

const token_t& parser_t::peek(int n)
{
  return tokens[current_ix + n];
}

const token_t& parser_t::advance()
{
  if (!at_end_p()) current_ix++;
  return previous();
}

bool parser_t::check(enum token_t::type_t token_type)
{
  if (at_end_p() && token_type != eof) return false;
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

expr_t * parser_t::immediate()
{
  match(hash); // optionally consume a hash
  expr_t * expr = expression();
  match(colon); // optionally consume a colon
  return expr;
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
  if      (match(number))     return new literal_t(std::get<num_t>(previous().literal));
  else if (match(identifier)) return new identifier_t(previous());

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
  case _m0:  return xy_src_t::m0;
  case _m1:  return xy_src_t::m1;
  case _m2:  return xy_src_t::m2;
  case _m3:  return xy_src_t::m3;
  case _mc0: return xy_src_t::mc0;
  case _mc1: return xy_src_t::mc1;
  case _mc2: return xy_src_t::mc2;
  case _mc3: return xy_src_t::mc3;
  default: assert(false); __builtin_unreachable();
  }
}

std::optional<op::d1_dest_t> parser_t::d1_dest()
{
  using namespace dsp::op;

  if      (match(_mc0)) return {d1_dest_t::mc0};
  else if (match(_mc1)) return {d1_dest_t::mc1};
  else if (match(_mc2)) return {d1_dest_t::mc2};
  else if (match(_mc3)) return {d1_dest_t::mc3};
  else if (match(_rx))  return {d1_dest_t::rx};
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

static op::d1_src_t d1_src(const token_t& token)
{
  using namespace dsp::op;

  switch (token.type) {
  case _m0:  return d1_src_t::m0;
  case _m1:  return d1_src_t::m1;
  case _m2:  return d1_src_t::m2;
  case _m3:  return d1_src_t::m3;
  case _mc0: return d1_src_t::mc0;
  case _mc1: return d1_src_t::mc1;
  case _mc2: return d1_src_t::mc2;
  case _mc3: return d1_src_t::mc3;
  case _all: return d1_src_t::all;
  case _alh: return d1_src_t::alh;
  default: assert(false); __builtin_unreachable();
  }
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
      uimm_t<8> imm = uimm_t<8>(peek(), immediate());
      consume(comma, "expected `,`");
      if (auto dest_o = d1_dest())
	return {new op::mov_imm_d1_t(imm, *dest_o)};
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
  bool saw_nop = false;
  std::vector<const op::op_t *> ops;
  std::vector<const token_t *> tokens;

  auto emplace_op = [&](const token_t& token, const op::op_t * a) {
    for (std::vector<const op::op_t *>::size_type i = 0; i < ops.size(); i++) {
      const op::op_t * b = ops[i];
      if ((a->mask() & b->mask() & ~(0b11 << 30)) != 0) {
	dsp::error(*tokens[i], "conflict");
	throw error(token, "conflict");
      }
    }
    tokens.emplace_back(&token);
    ops.emplace_back(a);
  };

  while (true) {
    // fixme: check for emplacement here
    const token_t& token = peek();
    if      (match(_nop))            saw_nop = 1;
    else if (auto op_o = alu()     ) emplace_op(token, *op_o);
    else if (auto op_o = xyd1_bus()) emplace_op(token, *op_o);
    else                               break;
  }
  if (ops.size() != 0 || saw_nop)
    return {new op::control_word_t(ops)};
  else
    return {};
}

load::dest_t parser_t::load_dest()
{
  using namespace dsp::load;

  if      (match(_mc0)) return dest_t::mc0;
  else if (match(_mc1)) return dest_t::mc1;
  else if (match(_mc2)) return dest_t::mc2;
  else if (match(_mc3)) return dest_t::mc3;
  else if (match(_rx))  return dest_t::rx;
  else if (match(_pl))  return dest_t::pl;
  else if (match(_ra0)) return dest_t::ra0;
  else if (match(_wa0)) return dest_t::wa0;
  else if (match(_lop)) return dest_t::lop;
  else if (match(_pc))  return dest_t::pc;
  else
    throw error(peek(), "expected mvi destination");
}

load::cond_t parser_t::load_cond()
{
  using namespace dsp::load;

  switch (advance().type) {
  case _z:   return cond_t::z;
  case _nz:  return cond_t::nz;
  case _s:   return cond_t::s;
  case _ns:  return cond_t::ns;
  case _c:   return cond_t::c;
  case _nc:  return cond_t::nc;
  case _t0:  return cond_t::t0;
  case _nt0: return cond_t::nt0;
  case _zs:  return cond_t::zs;
  case _nzs: return cond_t::nzs;
  default:
    throw error(previous(), "expected mvi condition after ','");
  }
}

std::optional<stmt_t *> parser_t::load()
{
  if (match(_mvi)) {
    const token_t& expr_token = peek();
    expr_t * expr = immediate();
    consume(comma, "expected `,`");
    load::dest_t dest = parser_t::load_dest();
    if (match(comma)) {
      load::cond_t cond = load_cond();
      uimm_t<19> imm = uimm_t<19>(expr_token, expr);
      return {new load::mvi_cond_t(imm, dest, cond)};
    } else {
      uimm_t<25> imm = uimm_t<25>(expr_token, expr);
      return {new load::mvi_t(imm, dest)};
    }
  } else
    return {};
}

static bool dma_p(const token_t& token)
{
  switch (token.type) {
  case _dmah:   [[fallthrough]];
  case _dmah0:  [[fallthrough]];
  case _dmah1:  [[fallthrough]];
  case _dmah2:  [[fallthrough]];
  case _dmah4:  [[fallthrough]];
  case _dmah8:  [[fallthrough]];
  case _dmah16: [[fallthrough]];
  case _dmah32: [[fallthrough]];
  case _dmah64: [[fallthrough]];
  case _dma:    [[fallthrough]];
  case _dma0:   [[fallthrough]];
  case _dma1:   [[fallthrough]];
  case _dma2:   [[fallthrough]];
  case _dma4:   [[fallthrough]];
  case _dma8:   [[fallthrough]];
  case _dma16:  [[fallthrough]];
  case _dma32:  [[fallthrough]];
  case _dma64:  return true;
  default:      return false;
  }
}

static bool dma_hold_p(const token_t& token)
{
  switch (token.type) {
  case _dmah:   [[fallthrough]];
  case _dmah0:  [[fallthrough]];
  case _dmah1:  [[fallthrough]];
  case _dmah2:  [[fallthrough]];
  case _dmah4:  [[fallthrough]];
  case _dmah8:  [[fallthrough]];
  case _dmah16: [[fallthrough]];
  case _dmah32: [[fallthrough]];
  case _dmah64: return true;
  case _dma:    [[fallthrough]];
  case _dma0:   [[fallthrough]];
  case _dma1:   [[fallthrough]];
  case _dma2:   [[fallthrough]];
  case _dma4:   [[fallthrough]];
  case _dma8:   [[fallthrough]];
  case _dma16:  [[fallthrough]];
  case _dma32:  [[fallthrough]];
  case _dma64:  return false;
  default: assert(false);
  }
}

static dma::add_mode_t dma_add(const token_t& token)
{
  using namespace dsp::dma;

  switch (token.type) {
  case _dma:    [[fallthrough]];
  case _dmah:   return add_mode_t::_1;
  case _dma0:   [[fallthrough]];
  case _dmah0:  return add_mode_t::_0;
  case _dma1:   [[fallthrough]];
  case _dmah1:  return add_mode_t::_1;
  case _dma2:   [[fallthrough]];
  case _dmah2:  return add_mode_t::_2;
  case _dma4:   [[fallthrough]];
  case _dmah4:  return add_mode_t::_4;
  case _dma8:   [[fallthrough]];
  case _dmah8:  return add_mode_t::_8;
  case _dma16:  [[fallthrough]];
  case _dmah16: return add_mode_t::_16;
  case _dma32:  [[fallthrough]];
  case _dmah32: return add_mode_t::_32;
  case _dma64:  [[fallthrough]];
  case _dmah64: return add_mode_t::_64;
  default: assert(false);
  }
}

dma::src_t parser_t::dma_src()
{
  switch (advance().type) {
  case _mc0: return dma::src_t::mc0;
  case _mc1: return dma::src_t::mc1;
  case _mc2: return dma::src_t::mc2;
  case _mc3: return dma::src_t::mc3;
  default:
    throw error(previous(), "expected dma source operand");
  }
}

dma::dst_t parser_t::dma_dst()
{
  switch (advance().type) {
  case _mc0: return dma::dst_t::mc0;
  case _mc1: return dma::dst_t::mc1;
  case _mc2: return dma::dst_t::mc2;
  case _mc3: return dma::dst_t::mc3;
  case _prg: return dma::dst_t::prg;
  default:
    throw error(previous(), "expected dma destination operand");
  }
}

std::optional<dma::length_ram_t> parser_t::dma_length_ram()
{
  using namespace dsp::dma;

  if      (match(_m0))  return length_ram_t::m0;
  else if (match(_m1))  return length_ram_t::m1;
  else if (match(_m2))  return length_ram_t::m2;
  else if (match(_m3))  return length_ram_t::m3;
  else if (match(_mc0)) return length_ram_t::mc0;
  else if (match(_mc1)) return length_ram_t::mc1;
  else if (match(_mc2)) return length_ram_t::mc2;
  else if (match(_mc3)) return length_ram_t::mc3;
  else                  return {};
}

std::optional<stmt_t *> parser_t::dma()
{
  if (dma_p(peek())) {
    const token_t& token = advance();
    bool hold = dma_hold_p(token);
    dma::add_mode_t add = dma_add(token);
    if        (match(_d0)) {
      consume(comma, "expected `,`");
      dma::dst_t dst = dma_dst();
      consume(comma, "expected `,`");
      if (auto length_ram_o = dma_length_ram()) {
	return {new dma::d0_dst_ram_t(hold, add, dst, *length_ram_o)};
      } else {
	uimm_t<8> imm = uimm_t<8>(peek(), immediate());
	return {new dma::d0_dst_imm_t(hold, add, dst, imm)};
      }
    } else {
      dma::src_t src = dma_src();
      consume(comma, "expected `,`");
      consume(_d0, "expected `d0`");
      consume(comma, "expected `,`");
      if (auto length_ram_o = dma_length_ram()) {
	return {new dma::src_d0_ram_t(hold, add, src, *length_ram_o)};
      } else {
	uimm_t<8> imm = uimm_t<8>(peek(), immediate());
	return {new dma::src_d0_imm_t(hold, add, src, imm)};
      }
    }
  } else
    return {};
}

std::optional<jump::cond_t> parser_t::jump_cond()
{
  using namespace dsp::jump;

  if      (match(_z))   return {cond_t::z};
  else if (match(_nz))  return {cond_t::nz};
  else if (match(_s))   return {cond_t::s};
  else if (match(_ns))  return {cond_t::ns};
  else if (match(_c))   return {cond_t::c};
  else if (match(_nc))  return {cond_t::nc};
  else if (match(_t0))  return {cond_t::t0};
  else if (match(_nt0)) return {cond_t::nt0};
  else if (match(_zs))  return {cond_t::zs};
  else if (match(_nzs)) return {cond_t::nzs};
  else                  return {};
}

std::optional<stmt_t *> parser_t::jump()
{
  if (match(_jmp)) {
    if (auto cond_o = jump_cond()) {
      consume(comma, "expected `,` after jump condition");
      uimm_t<8> imm = uimm_t<8>(peek(), immediate());
      return {new jump::jmp_cond_t(*cond_o, imm)};
    } else {
      uimm_t<8> imm = uimm_t<8>(peek(), immediate());
      return {new jump::jmp_t(imm)};
    }
  } else
    return {};
}

std::optional<stmt_t *> parser_t::loop()
{
  if      (match(_btm)) return {new loop::btm_t()};
  else if (match(_lps)) return {new loop::lps_t()};
  else                  return {};
}

std::optional<stmt_t *> parser_t::end()
{
  if      (match(_end))  return {new end::end_t()};
  else if (match(_endi)) return {new end::endi_t()};
  else                   return {};
}

std::optional<stmt_t *> parser_t::instruction()
{
  if      (auto op_o = op())     return op_o;
  else if (auto load_o = load()) return load_o;
  else if (auto dma_o = dma())   return dma_o;
  else if (auto jump_o = jump()) return jump_o;
  else if (auto loop_o = loop()) return loop_o;
  else if (auto end_o = end())   return end_o;
  else                           return {};
}

std::optional<stmt_t *> parser_t::statement()
{
  if (check(eol)) {
    while (!at_end_p() && check(eol)) advance();
    return statement();
  } else if (check(eof)) {
    return {};
  } else if (match(identifier)) {
    token_t name = previous();
    if (match(colon)) {
      return {new label_t(name)};
    } else if (match(equal) || match(_equ)) {
      expr_t * value = expression();
      if (check(eol) || check(eof))
	return {new assign_t(name, value)};
      else
      	throw error(peek(), "expected eol or eof after assignment");
    } else {
      throw error(peek(), "expected assignment or label");
    }
  } else if (auto ins_o = instruction()) {
    if (check(eol) || check(eof))
      return ins_o;
    else
      throw error(peek(), "expected eol or eof after instruction");
  } else {
    auto exc = error(peek(), "expected statement");
    advance();
    if (check(equal) || check(_equ))
      std::cerr << "hint: it is not legal to assign a value to a keyword" << std::endl;
    throw exc;
  }
}

}
