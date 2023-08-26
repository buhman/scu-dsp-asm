namespace dsp {

namespace op {

static uint32_t alu_bits(alu_type_t type)
{
  using enum alu_type_t;
  switch (type) {
    case alu_type_t::andl: return 0b0001 << 26;
    case alu_type_t::orl:  return 0b0010 << 26;
    case alu_type_t::xorl: return 0b0011 << 26;
    case alu_type_t::add:  return 0b0100 << 26;
    case alu_type_t::sub:  return 0b0101 << 26;
    case alu_type_t::ad2:  return 0b0110 << 26;
    case alu_type_t::sr:   return 0b1000 << 26;
    case alu_type_t::rr:   return 0b1001 << 26;
    case alu_type_t::sl:   return 0b1010 << 26;
    case alu_type_t::rl:   return 0b1011 << 26;
    case alu_type_t::rl8:  return 0b1111 << 26;
    default: __builtin_unreachable();
  }
}

static uint32_t xy_src_bits(xy_src_t src, int shift)
{
  using enum xy_src_t;

  switch (src) {
  case m0:  return 0b000 << shift;
  case m1:  return 0b001 << shift;
  case m2:  return 0b010 << shift;
  case m3:  return 0b011 << shift;
  case mc0: return 0b100 << shift;
  case mc1: return 0b101 << shift;
  case mc2: return 0b110 << shift;
  case mc3: return 0b111 << shift;
  default: __builtin_unreachable();
  }
}

static uint32_t d1_dest_bits(d1_dest_t dest)
{
  using enum d1_dest_t;

  switch (dest) {
  case mc0: return 0b0000 << 8;
  case mc1: return 0b0001 << 8;
  case mc2: return 0b0010 << 8;
  case mc3: return 0b0011 << 8;
  case rx:  return 0b0100 << 8;
  case pl:  return 0b0101 << 8;
  case ra0: return 0b0110 << 8;
  case wa0: return 0b0111 << 8;
  case lop: return 0b1010 << 8;
  case top: return 0b1011 << 8;
  case ct0: return 0b1100 << 8;
  case ct1: return 0b1101 << 8;
  case ct2: return 0b1110 << 8;
  case ct3: return 0b1111 << 8;
  default: __builtin_unreachable();
  }
}

static uint32_t d1_src_bits(d1_src_t src)
{
  using enum d1_src_t;

  switch (src) {
  case m0:  return 0b0000 << 0;
  case m1:  return 0b0001 << 0;
  case m2:  return 0b0010 << 0;
  case m3:  return 0b0011 << 0;
  case mc0: return 0b0100 << 0;
  case mc1: return 0b0101 << 0;
  case mc2: return 0b0110 << 0;
  case mc3: return 0b0111 << 0;
  case all: return 0b1001 << 0;
  case alh: return 0b1010 << 0;
  default: __builtin_unreachable();
  }
}

} // op

namespace load {

static uint32_t dest_bits(dest_t dest)
{
  using enum dest_t;

  switch (dest) {
  case mc0: return 0b0000 << 26;
  case mc1: return 0b0001 << 26;
  case mc2: return 0b0010 << 26;
  case mc3: return 0b0011 << 26;
  case rx:  return 0b0100 << 26;
  case pl:  return 0b0101 << 26;
  case ra0: return 0b0110 << 26;
  case wa0: return 0b0111 << 26;
  case lop: return 0b1010 << 26;
  case pc:  return 0b1100 << 26;
  default: __builtin_unreachable();
  }
}

static uint32_t cond_bits(cond_t cond)
{
  using enum cond_t;

  switch (cond) {
  case z:   return 0b1'0'0001 << 19;
  case nz:  return 0b0'0'0001 << 19;
  case s:   return 0b1'0'0010 << 19;
  case ns:  return 0b0'0'0010 << 19;
  case c:   return 0b1'0'0100 << 19;
  case nc:  return 0b0'0'0100 << 19;
  case t0:  return 0b1'0'1000 << 19;
  case nt0: return 0b0'0'1000 << 19;
  case zs:  return 0b1'0'0011 << 19;
  case nzs: return 0b0'0'0011 << 19;
  default: __builtin_unreachable();
  }
}

} // load

namespace dma {

static uint32_t add_mode_bits(add_mode_t add)
{
  using enum add_mode_t;

  switch (add) {
  case _0 : return 0b000 << 15;
  case _1 : return 0b001 << 15;
  case _2 : return 0b010 << 15;
  case _4 : return 0b011 << 15;
  case _8 : return 0b100 << 15;
  case _16: return 0b101 << 15;
  case _32: return 0b110 << 15;
  case _64: return 0b111 << 15;
  default: __builtin_unreachable();
  }
}

static uint32_t hold_bits(bool hold)
{
  return hold ? (1 << 14)
              : (0 << 14)
              ;
}

static uint32_t src_bits(src_t src)
{
  using enum src_t;

  switch (src) {
  case mc0: return 0b000 << 8;
  case mc1: return 0b001 << 8;
  case mc2: return 0b010 << 8;
  case mc3: return 0b011 << 8;
  default: __builtin_unreachable();
  }
}

static uint32_t dst_bits(dst_t dst)
{
  using enum dst_t;

  switch (dst) {
  case mc0: return 0b000 << 8;
  case mc1: return 0b001 << 8;
  case mc2: return 0b010 << 8;
  case mc3: return 0b011 << 8;
  case prg: return 0b100 << 8;
  default: __builtin_unreachable();
  }
}

static uint32_t length_ram_bits(length_ram_t ram)
{
  using enum length_ram_t;

  switch (ram) {
  case m0 : return 0b000 << 0;
  case m1 : return 0b001 << 0;
  case m2 : return 0b010 << 0;
  case m3 : return 0b011 << 0;
  case mc0: return 0b100 << 0;
  case mc1: return 0b101 << 0;
  case mc2: return 0b110 << 0;
  case mc3: return 0b111 << 0;
  default: __builtin_unreachable();
  }
}

} // dma

namespace jump {

static uint32_t cond_bits(cond_t cond)
{
  using enum cond_t;

  switch (cond) {
  case z  : return 0b100'001 << 19;
  case nz : return 0b000'001 << 19;
  case s  : return 0b100'010 << 19;
  case ns : return 0b000'010 << 19;
  case c  : return 0b100'100 << 19;
  case nc : return 0b000'100 << 19;
  case t0 : return 0b101'000 << 19;
  case nt0: return 0b001'000 << 19;
  case zs : return 0b100'011 << 19;
  case nzs: return 0b000'011 << 19;
  default: __builtin_unreachable();
  }
}

} // jump

} // dsp
