#pragma once

namespace dsp {

namespace op {

enum struct alu_type_t : int {
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

enum struct xy_src_t {
  m0 , m1 , m2 , m3 ,
  mc0, mc1, mc2, mc3,
};

enum struct d1_dest_t {
  mc0, mc1, mc2, mc3,
  rx , pl ,
  ra0, wa0,
  lop, top,
  ct0, ct1, ct2, ct3,
};

enum struct d1_src_t {
  m0 , m1 , m2 , m3 ,
  mc0, mc1, mc2, mc3,
  all, alh,
};

}

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

enum struct src_t {
  m0, m1, m2, m3
};

enum struct dst_t {
  m0, m1, m2, m3,
  prg,
};

enum struct length_ram_t {
  m0 , m1 , m2 , m3 ,
  mc0, mc1, mc2, mc3,
};

} // dma

namespace jump {

enum struct cond_t {
  z , nz ,
  s , ns ,
  c , nc ,
  t0, nt0,
  zs, nzs,
};

} // jump

}
