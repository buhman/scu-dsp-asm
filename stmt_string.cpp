#include "stmt_string.hpp"
#include "stmt_ins.hpp"

#define i(v) (static_cast<int>(v))

namespace dsp {

namespace op {

const std::string x_src_string[] = {
  [i(x_src_t::m0 )] = "m0" ,
  [i(x_src_t::m1 )] = "m1" ,
  [i(x_src_t::m2 )] = "m2" ,
  [i(x_src_t::m3 )] = "m3" ,
  [i(x_src_t::mc0)] = "mc0",
  [i(x_src_t::mc1)] = "mc1",
  [i(x_src_t::mc2)] = "mc2",
  [i(x_src_t::mc3)] = "mc3",
};

const std::string y_src_string[] = {
  [i(y_src_t::m0 )] = "m0" ,
  [i(y_src_t::m1 )] = "m1" ,
  [i(y_src_t::m2 )] = "m2" ,
  [i(y_src_t::m3 )] = "m3" ,
  [i(y_src_t::mc0)] = "mc0",
  [i(y_src_t::mc1)] = "mc1",
  [i(y_src_t::mc2)] = "mc2",
  [i(y_src_t::mc3)] = "mc3",
};

const std::string d1_dst_string[] = {
  [i(d1_dst_t::mc0)] = "mc0",
  [i(d1_dst_t::mc1)] = "mc1",
  [i(d1_dst_t::mc2)] = "mc2",
  [i(d1_dst_t::mc3)] = "mc3",
  [i(d1_dst_t::rx )] = "rx" ,
  [i(d1_dst_t::pl )] = "pl" ,
  [i(d1_dst_t::ra0)] = "ra0",
  [i(d1_dst_t::wa0)] = "wa0",
  [i(d1_dst_t::lop)] = "lop",
  [i(d1_dst_t::top)] = "top",
  [i(d1_dst_t::ct0)] = "ct0",
  [i(d1_dst_t::ct1)] = "ct1",
  [i(d1_dst_t::ct2)] = "ct2",
  [i(d1_dst_t::ct3)] = "ct3",
};

const std::string d1_src_string[] = {
  [i(d1_src_t::m0 )] = "m0" ,
  [i(d1_src_t::m1 )] = "m1" ,
  [i(d1_src_t::m2 )] = "m2" ,
  [i(d1_src_t::m3 )] = "m3" ,
  [i(d1_src_t::mc0)] = "mc0",
  [i(d1_src_t::mc1)] = "mc1",
  [i(d1_src_t::mc2)] = "mc2",
  [i(d1_src_t::mc3)] = "mc3",
  [i(d1_src_t::all)] = "all",
  [i(d1_src_t::alh)] = "alh",
};

}

namespace load {

const std::string dst_string[] = {
  [i(dst_t::mc0)] = "mc0",
  [i(dst_t::mc1)] = "mc1",
  [i(dst_t::mc2)] = "mc2",
  [i(dst_t::mc3)] = "mc3",
  [i(dst_t::rx )] = "rx" ,
  [i(dst_t::pl )] = "pl" ,
  [i(dst_t::ra0)] = "ra0",
  [i(dst_t::wa0)] = "wa0",
  [i(dst_t::lop)] = "lop",
  [i(dst_t::pc )] = "pc" ,
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
  [i(add_t::_0 )] = "0" ,
  [i(add_t::_1 )] = "1" ,
  [i(add_t::_2 )] = "2" ,
  [i(add_t::_4 )] = "4" ,
  [i(add_t::_8 )] = "8" ,
  [i(add_t::_16)] = "16",
  [i(add_t::_32)] = "32",
  [i(add_t::_64)] = "64",
};

const std::string src_string[] = {
  [i(src_t::mc0)] = "mc0",
  [i(src_t::mc1)] = "mc1",
  [i(src_t::mc2)] = "mc2",
  [i(src_t::mc3)] = "mc3"
};

const std::string dst_string[] = {
  [i(dst_t::mc0)] = "mc0",
  [i(dst_t::mc1)] = "mc1",
  [i(dst_t::mc2)] = "mc2",
  [i(dst_t::mc3)] = "mc3",
  [i(dst_t::prg)] = "prg",
};

const std::string length_ram_string[] = {
  [i(ram_t::m0 )] = "m0" ,
  [i(ram_t::m1 )] = "m1" ,
  [i(ram_t::m2 )] = "m2" ,
  [i(ram_t::m3 )] = "m3" ,
  [i(ram_t::mc0)] = "mc0",
  [i(ram_t::mc1)] = "mc1",
  [i(ram_t::mc2)] = "mc2",
  [i(ram_t::mc3)] = "mc3",
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
