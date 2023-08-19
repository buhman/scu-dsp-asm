#include <vector>

#include "expr.hpp"

namespace dsp {

/*
struct assign_t : stmt_accept_t<assign_t>
{
  assign_t(token_t name, expr_t * value)
    : name(name), value(value) {}

  const token_t name;
  const expr_t * value;
};
*/

template <bool S, int N>
struct imm_t {
  const expr_t * expr;

  static constexpr bool sign = S;
  static constexpr int bits = N;
};

template <int N>
using simm_t = imm_t<true, N>;

template <int N>
using uimm_t = imm_t<false, N>;

namespace op {

enum alu_type_t {
  andl,
  orl,
  xorl,
  add,
  sub,
  ad2,
  sr,
  rr,
  sl,
  rl,
  rl8,
};

struct alu_t {
  const alu_type_t type;
};

enum struct xy_src_t {
  mc0, mc1, mc2, mc3,
  m0 , m1 , m2 ,  m3,
};

struct op_t {
};

struct mov_ram_x_t : op_t {
  const xy_src_t src;
};

struct mov_mul_p_t : op_t {
};

struct mov_ram_p_t : op_t {
  const xy_src_t src;
};

struct mov_ram_y_t : op_t {
  const xy_src_t src;
};

struct clr_a_t : op_t {
};

struct mov_alu_a_t : op_t {
};

struct mov_ram_a_t : op_t {
  const xy_src_t src;
};

enum struct d1_dest_t {
  rx , pl ,
  ra0, wa0,
  lop, top,
  ct0, ct1, ct2, ct3,
};

enum struct d1_src_t {
  mc0, mc1, mc2, mc3,
  m0 , m1 , m2 , m3 ,
};

struct mov_imm_d1 : op_t {
  const simm_t<8> imm;
  const d1_dest_t dest;
};

struct mov_ram_d1 : op_t {
  const d1_src_t src;
  const d1_dest_t dest;
};

struct instruction_t {
  const std::vector<op_t *> ops;
};

} // op

namespace load {

enum struct dest_t {
  mc0, mc1, mc2, mc3,
  rx , pl ,
  ra0, wa0,
  lop, pc ,
};

enum struct cond_t {
  z , nz ,
  s , ns ,
  c , nc ,
  t0, nt0,
  zs, nzs,
};

struct mvi_t {
  const uimm_t<25> imm;
};

struct mvi_cond_t {
  const uimm_t<19> imm;
};

} // load

namespace dma {

enum struct add_mode_t {
  _0 ,
  _1 ,
  _2 ,
  _4 ,
  _8 ,
  _16,
  _32,
  _64,
};

enum struct ingress_t {
  m0, m1, m2, m3
};

enum struct egress_t {
  m0, m1, m2, m3,
  prg,
};

struct ingress_imm_t {
  const bool hold;
  const ingress_t ingress;
  const simm_t<8> imm;
};

struct egress_imm_t {
  const bool hold;
  const egress_t egress;
  const simm_t<8> imm;
};

enum struct length_ram_t {
  m0, m1, m2, m3,
  mc0, mc1, mc2, mc3,
};

struct ingress_ram_t {
  const bool hold;
  const ingress_t ingress;
  const length_ram_t ram;
};

struct egress_ram_t {
  const bool hold;
  const egress_t egress;
  const length_ram_t ram;
};

} // dma

namespace jump
{

enum struct cond_t {
  z , nz,
  s , ns,
  c , nc,
  t0, nt0,
  zs, nzs,
};

struct jmp_t {
  uimm_t<8> imm;
};

struct jmp_cond_t {
  uimm_t<8> imm;
  cond_t cond;
};

} // jump

namespace loop {

struct btm_t {
};

struct lps_t {
};

} // loop

namespace end {

struct end_t {
};

struct endi_t {
};

} // loop

} // dsp
