#include <vector>

#include "expr.hpp"

namespace dsp {

struct stmt_t
{
  virtual void accept(visitor_t<void> const * visitor) const = 0;
  virtual std::string accept(visitor_t<std::string> const * visitor) const = 0;
};

template <typename T>
struct stmt_accept_t : stmt_t {
    virtual void accept(visitor_t<void> const * visitor) const {
      return visitor->visit(static_cast<const T*>(this));
    }

    virtual std::string accept(visitor_t<std::string> const * visitor) const
    {
      return visitor->visit(static_cast<const T*>(this));
    }
};

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

struct alu_t : stmt_accept_t<alu_t>
{
  alu_t(alu_type_t type)
    : type(type) {}

  const alu_type_t type;
};

enum struct xy_src_t {
  mc0, mc1, mc2, mc3,
  m0 , m1 , m2 ,  m3,
};

struct op_t : stmt_accept_t<op_t>
{
};

struct mov_ram_x_t : virtual op_t
{
  mov_ram_x_t(xy_src_t src)
    : src(src) {}

  const xy_src_t src;
};

struct mov_mul_p_t : op_t
{
  mov_mul_p_t() {}
};

struct mov_ram_p_t : op_t
{
  mov_ram_p_t(xy_src_t src)
    : src(src) {}

  const xy_src_t src;
};

struct mov_ram_y_t : op_t
{
  mov_ram_y_t(xy_src_t src)
    : src(src) {}

  const xy_src_t src;
};

struct clr_a_t : op_t
{
  clr_a_t() {}
};

struct mov_alu_a_t : op_t
{
  mov_alu_a_t() {}
};

struct mov_ram_a_t : op_t
{
  mov_ram_a_t(xy_src_t src)
    : src(src) {}

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

struct mov_imm_d1 : op_t
{
  mov_imm_d1(simm_t<8> imm, d1_dest_t dest)
    : imm(imm), dest(dest) {}

  const simm_t<8> imm;
  const d1_dest_t dest;
};

struct mov_ram_d1 : op_t
{
  mov_ram_d1(d1_src_t src, d1_dest_t dest)
    : src(src), dest(dest) {}

  const d1_src_t src;
  const d1_dest_t dest;
};

struct instruction_t : stmt_accept_t<instruction_t>
{
  instruction_t(std::vector<op_t *> ops)
    : ops(ops) {}

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

struct mvi_t : stmt_accept_t<mvi_t>
{
  mvi_t(uimm_t<25> imm)
    : imm(imm) {}

  const uimm_t<25> imm;
};

struct mvi_cond_t : stmt_accept_t<mvi_cond_t>
{
  mvi_cond_t(uimm_t<19> imm)
    : imm(imm) {}

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

struct ingress_imm_t : stmt_accept_t<ingress_imm_t>
{
  ingress_imm_t(bool hold, ingress_t ingress, simm_t<8> imm)
    : hold(hold), ingress(ingress), imm(imm) {}

  const bool hold;
  const ingress_t ingress;
  const simm_t<8> imm;
};

struct egress_imm_t : stmt_accept_t<egress_imm_t>
{
  egress_imm_t(bool hold, egress_t egress, simm_t<8> imm)
    : hold(hold), egress(egress), imm(imm) {}

  const bool hold;
  const egress_t egress;
  const simm_t<8> imm;
};

enum struct length_ram_t {
  m0 , m1 , m2 , m3 ,
  mc0, mc1, mc2, mc3,
};

struct ingress_ram_t : stmt_accept_t<ingress_ram_t>
{
  ingress_ram_t(bool hold, ingress_t ingress, length_ram_t ram)
    : hold(hold), ingress(ingress), ram(ram) {}

  const bool hold;
  const ingress_t ingress;
  const length_ram_t ram;
};

struct egress_ram_t : stmt_accept_t<egress_ram_t>
{
  egress_ram_t(bool hold, egress_t egress, length_ram_t ram)
    : hold(hold), egress(egress), ram(ram) {}

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

struct jmp_t : stmt_accept_t<jmp_t>
{
  jmp_t(uimm_t<8> imm)
    : imm(imm) {}

  const uimm_t<8> imm;
};

struct jmp_cond_t : stmt_accept_t<jmp_cond_t>
{
  jmp_cond_t(uimm_t<8> imm, cond_t cond)
    : imm(imm), cond(cond) {}

  const uimm_t<8> imm;
  const cond_t cond;
};

} // jump

namespace loop {

struct btm_t : stmt_accept_t<btm_t>
{
};

struct lps_t : stmt_accept_t<lps_t>
{
};

} // loop

namespace end {

struct end_t : stmt_accept_t<end_t>
{
};

struct endi_t : stmt_accept_t<endi_t>
{
};

} // end

/*
struct assign_t : stmt_accept_t<assign_t>
{
  assign_t(token_t name, expr_t * value)
    : name(name), value(value) {}

  const token_t name;
  const expr_t * value;
};
*/

} // dsp
