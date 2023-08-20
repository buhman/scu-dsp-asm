#include "stmt_string.hpp"
#include "stmt_enum.hpp"

#define i(v) (static_cast<int>(v))

namespace dsp {

namespace op {

const std::string alu_type_string[] = {
  [i(alu_type_t::andl)] = "andl",
  [i(alu_type_t::orl )] = "orl",
  [i(alu_type_t::xorl)] = "xorl",
  [i(alu_type_t::add )] = "add",
  [i(alu_type_t::sub )] = "sub",
  [i(alu_type_t::ad2 )] = "ad2",
  [i(alu_type_t::sr  )] = "sr",
  [i(alu_type_t::rr  )] = "rr",
  [i(alu_type_t::sl  )] = "sl",
  [i(alu_type_t::rl  )] = "rl",
  [i(alu_type_t::rl8 )] = "rl8",
};

const std::string xy_src_string[] = {
  [i(xy_src_t::mc0)] = "mc0",
  [i(xy_src_t::mc1)] = "mc1",
  [i(xy_src_t::mc2)] = "mc2",
  [i(xy_src_t::mc3)] = "mc3",
  [i(xy_src_t::m0 )] = "m0" ,
  [i(xy_src_t::m1 )] = "m1" ,
  [i(xy_src_t::m2 )] = "m2" ,
  [i(xy_src_t::m3 )] = "m3" ,
};

const std::string d1_dest_string[] = {
  [i(d1_dest_t::rx )] = "rx" ,
  [i(d1_dest_t::pl )] = "pl" ,
  [i(d1_dest_t::ra0)] = "ra0",
  [i(d1_dest_t::wa0)] = "wa0",
  [i(d1_dest_t::lop)] = "lop",
  [i(d1_dest_t::top)] = "top",
  [i(d1_dest_t::ct0)] = "ct0",
  [i(d1_dest_t::ct1)] = "ct1",
  [i(d1_dest_t::ct2)] = "ct2",
  [i(d1_dest_t::ct3)] = "ct3",
};

const std::string d1_src_string[] = {
  [i(d1_src_t::mc0)] = "mc0",
  [i(d1_src_t::mc1)] = "mc1",
  [i(d1_src_t::mc2)] = "mc2",
  [i(d1_src_t::mc3)] = "mc3",
  [i(d1_src_t::m0 )] = "m0" ,
  [i(d1_src_t::m1 )] = "m1" ,
  [i(d1_src_t::m2 )] = "m2" ,
  [i(d1_src_t::m3 )] = "m3" ,
};

}

namespace load {

const std::string dest_string[] = {
  [i(dest_t::mc0)] = "mc0",
  [i(dest_t::mc1)] = "mc1",
  [i(dest_t::mc2)] = "mc2",
  [i(dest_t::mc3)] = "mc3",
  [i(dest_t::rx )] = "rx" ,
  [i(dest_t::pl )] = "pl" ,
  [i(dest_t::ra0)] = "ra0",
  [i(dest_t::wa0)] = "wa0",
  [i(dest_t::lop)] = "lop",
  [i(dest_t::pc )] = "pc" ,
};

const std::string cond_string[] = {
  [i(cond_t::z  )] = "z" ,
  [i(cond_t::nz )] = "nz" ,
  [i(cond_t::s  )] = "s" ,
  [i(cond_t::ns )] = "ns" ,
  [i(cond_t::c  )] = "c" ,
  [i(cond_t::nc )] = "nc" ,
  [i(cond_t::t0 )] = "t0",
  [i(cond_t::nt0)] = "nt0",
  [i(cond_t::zs )] = "zs",
  [i(cond_t::nzs)] = "nzs",
};

} // load

namespace dma {

const std::string hold_mode_string[] = {
  [i(false)] = "dma",
  [i(true )] = "dmah",
};

const std::string add_mode_string[] = {
  [i(add_mode_t::_0 )] = "0" ,
  [i(add_mode_t::_1 )] = "1" ,
  [i(add_mode_t::_2 )] = "2" ,
  [i(add_mode_t::_4 )] = "4" ,
  [i(add_mode_t::_8 )] = "8" ,
  [i(add_mode_t::_16)] = "16",
  [i(add_mode_t::_32)] = "32",
  [i(add_mode_t::_64)] = "64",
};

const std::string ingress_string[] = {
  [i(ingress_t::m0)] = "m0",
  [i(ingress_t::m1)] = "m1",
  [i(ingress_t::m2)] = "m2",
  [i(ingress_t::m3)] = "m3"
};

const std::string egress_string[] = {
  [i(egress_t::m0 )] = "m0",
  [i(egress_t::m1 )] = "m1",
  [i(egress_t::m2 )] = "m2",
  [i(egress_t::m3 )] = "m3",
  [i(egress_t::prg)] = "prg",
};

const std::string length_ram_string[] = {
  [i(length_ram_t::m0 )] = "m0" ,
  [i(length_ram_t::m1 )] = "m1" ,
  [i(length_ram_t::m2 )] = "m2" ,
  [i(length_ram_t::m3 )] = "m3" ,
  [i(length_ram_t::mc0)] = "mc0",
  [i(length_ram_t::mc1)] = "mc1",
  [i(length_ram_t::mc2)] = "mc2",
  [i(length_ram_t::mc3)] = "mc3",
};

} // dma

namespace jump {

const std::string cond_string[] = {
  [i(cond_t::z  )] = "z" ,
  [i(cond_t::nz )] = "nz",
  [i(cond_t::s  )] = "s" ,
  [i(cond_t::ns )] = "ns",
  [i(cond_t::c  )] = "c" ,
  [i(cond_t::nc )] = "nc",
  [i(cond_t::t0 )] = "t0",
  [i(cond_t::nt0)] = "nt0",
  [i(cond_t::zs )] = "zs",
  [i(cond_t::nzs)] = "nzs",
};

} // jump

}

#undef i
