#pragma once

#include <cstdint>
#include <iostream>

#include "imm.hpp"
#include "ins.hpp"
#include "stmt_base.hpp"

namespace dsp {
  namespace op {
    
    struct x_src_t {
      enum value_t {
        m0,
        m1,
        m2,
        m3,
        mc0,
        mc1,
        mc2,
        mc3,
      };
      
      const value_t value;
      
      constexpr x_src_t(value_t value)
        : value(value) {}
      
      constexpr x_src_t(uint32_t code)
        : value(to_value(code)) {}
      
      static constexpr uint32_t mask() { return 0b111 << 20; }
      
      static constexpr value_t to_value(uint32_t code)
      {
        using enum value_t;
        
        switch (code & mask()) {
          case 0b000 << 20: return m0;
          case 0b001 << 20: return m1;
          case 0b010 << 20: return m2;
          case 0b011 << 20: return m3;
          case 0b100 << 20: return mc0;
          case 0b101 << 20: return mc1;
          case 0b110 << 20: return mc2;
          case 0b111 << 20: return mc3;
          default:
            std::cerr << "invalid op x_src code: " << (code & mask()) << std::endl;
            throw std::runtime_error("invalid code");
        }
      }
      
      uint32_t bits() const
      {
        using enum value_t;
        
        switch (value) {
          case m0: return 0b000 << 20;
          case m1: return 0b001 << 20;
          case m2: return 0b010 << 20;
          case m3: return 0b011 << 20;
          case mc0: return 0b100 << 20;
          case mc1: return 0b101 << 20;
          case mc2: return 0b110 << 20;
          case mc3: return 0b111 << 20;
          default: __builtin_unreachable();
        }
      }
    };
    
    struct y_src_t {
      enum value_t {
        m0,
        m1,
        m2,
        m3,
        mc0,
        mc1,
        mc2,
        mc3,
      };
      
      const value_t value;
      
      constexpr y_src_t(value_t value)
        : value(value) {}
      
      constexpr y_src_t(uint32_t code)
        : value(to_value(code)) {}
      
      static constexpr uint32_t mask() { return 0b111 << 14; }
      
      static constexpr value_t to_value(uint32_t code)
      {
        using enum value_t;
        
        switch (code & mask()) {
          case 0b000 << 14: return m0;
          case 0b001 << 14: return m1;
          case 0b010 << 14: return m2;
          case 0b011 << 14: return m3;
          case 0b100 << 14: return mc0;
          case 0b101 << 14: return mc1;
          case 0b110 << 14: return mc2;
          case 0b111 << 14: return mc3;
          default:
            std::cerr << "invalid op y_src code: " << (code & mask()) << std::endl;
            throw std::runtime_error("invalid code");
        }
      }
      
      uint32_t bits() const
      {
        using enum value_t;
        
        switch (value) {
          case m0: return 0b000 << 14;
          case m1: return 0b001 << 14;
          case m2: return 0b010 << 14;
          case m3: return 0b011 << 14;
          case mc0: return 0b100 << 14;
          case mc1: return 0b101 << 14;
          case mc2: return 0b110 << 14;
          case mc3: return 0b111 << 14;
          default: __builtin_unreachable();
        }
      }
    };
    
    struct d1_src_t {
      enum value_t {
        m0,
        m1,
        m2,
        m3,
        mc0,
        mc1,
        mc2,
        mc3,
        all,
        alh,
      };
      
      const value_t value;
      
      constexpr d1_src_t(value_t value)
        : value(value) {}
      
      constexpr d1_src_t(uint32_t code)
        : value(to_value(code)) {}
      
      static constexpr uint32_t mask() { return 0b1111 << 0; }
      
      static constexpr value_t to_value(uint32_t code)
      {
        using enum value_t;
        
        switch (code & mask()) {
          case 0b0000 << 0: return m0;
          case 0b0001 << 0: return m1;
          case 0b0010 << 0: return m2;
          case 0b0011 << 0: return m3;
          case 0b0100 << 0: return mc0;
          case 0b0101 << 0: return mc1;
          case 0b0110 << 0: return mc2;
          case 0b0111 << 0: return mc3;
          case 0b1001 << 0: return all;
          case 0b1010 << 0: return alh;
          default:
            std::cerr << "invalid op d1_src code: " << (code & mask()) << std::endl;
            throw std::runtime_error("invalid code");
        }
      }
      
      uint32_t bits() const
      {
        using enum value_t;
        
        switch (value) {
          case m0: return 0b0000 << 0;
          case m1: return 0b0001 << 0;
          case m2: return 0b0010 << 0;
          case m3: return 0b0011 << 0;
          case mc0: return 0b0100 << 0;
          case mc1: return 0b0101 << 0;
          case mc2: return 0b0110 << 0;
          case mc3: return 0b0111 << 0;
          case all: return 0b1001 << 0;
          case alh: return 0b1010 << 0;
          default: __builtin_unreachable();
        }
      }
    };
    
    struct d1_dst_t {
      enum value_t {
        mc0,
        mc1,
        mc2,
        mc3,
        rx,
        pl,
        ra0,
        wa0,
        lop,
        top,
        ct0,
        ct1,
        ct2,
        ct3,
      };
      
      const value_t value;
      
      constexpr d1_dst_t(value_t value)
        : value(value) {}
      
      constexpr d1_dst_t(uint32_t code)
        : value(to_value(code)) {}
      
      static constexpr uint32_t mask() { return 0b1111 << 8; }
      
      static constexpr value_t to_value(uint32_t code)
      {
        using enum value_t;
        
        switch (code & mask()) {
          case 0b0000 << 8: return mc0;
          case 0b0001 << 8: return mc1;
          case 0b0010 << 8: return mc2;
          case 0b0011 << 8: return mc3;
          case 0b0100 << 8: return rx;
          case 0b0101 << 8: return pl;
          case 0b0110 << 8: return ra0;
          case 0b0111 << 8: return wa0;
          case 0b1010 << 8: return lop;
          case 0b1011 << 8: return top;
          case 0b1100 << 8: return ct0;
          case 0b1101 << 8: return ct1;
          case 0b1110 << 8: return ct2;
          case 0b1111 << 8: return ct3;
          default:
            std::cerr << "invalid op d1_dst code: " << (code & mask()) << std::endl;
            throw std::runtime_error("invalid code");
        }
      }
      
      uint32_t bits() const
      {
        using enum value_t;
        
        switch (value) {
          case mc0: return 0b0000 << 8;
          case mc1: return 0b0001 << 8;
          case mc2: return 0b0010 << 8;
          case mc3: return 0b0011 << 8;
          case rx: return 0b0100 << 8;
          case pl: return 0b0101 << 8;
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
    };
    
    struct andl_t : stmt_accept_t<andl_t>, ins_t<andl_t>
    {
      
      andl_t()
      {}
      
      andl_t(uint32_t code)
      { (void)code; }
      
      
      static uint32_t mask() { return 0b1111 << 26; }
      static uint32_t code() { return 0b0001 << 26; }
      uint32_t bits() const { return 0; }
    };
    
    struct orl_t : stmt_accept_t<orl_t>, ins_t<orl_t>
    {
      
      orl_t()
      {}
      
      orl_t(uint32_t code)
      { (void)code; }
      
      
      static uint32_t mask() { return 0b1111 << 26; }
      static uint32_t code() { return 0b0010 << 26; }
      uint32_t bits() const { return 0; }
    };
    
    struct xorl_t : stmt_accept_t<xorl_t>, ins_t<xorl_t>
    {
      
      xorl_t()
      {}
      
      xorl_t(uint32_t code)
      { (void)code; }
      
      
      static uint32_t mask() { return 0b1111 << 26; }
      static uint32_t code() { return 0b0011 << 26; }
      uint32_t bits() const { return 0; }
    };
    
    struct add_t : stmt_accept_t<add_t>, ins_t<add_t>
    {
      
      add_t()
      {}
      
      add_t(uint32_t code)
      { (void)code; }
      
      
      static uint32_t mask() { return 0b1111 << 26; }
      static uint32_t code() { return 0b0100 << 26; }
      uint32_t bits() const { return 0; }
    };
    
    struct sub_t : stmt_accept_t<sub_t>, ins_t<sub_t>
    {
      
      sub_t()
      {}
      
      sub_t(uint32_t code)
      { (void)code; }
      
      
      static uint32_t mask() { return 0b1111 << 26; }
      static uint32_t code() { return 0b0101 << 26; }
      uint32_t bits() const { return 0; }
    };
    
    struct ad2_t : stmt_accept_t<ad2_t>, ins_t<ad2_t>
    {
      
      ad2_t()
      {}
      
      ad2_t(uint32_t code)
      { (void)code; }
      
      
      static uint32_t mask() { return 0b1111 << 26; }
      static uint32_t code() { return 0b0110 << 26; }
      uint32_t bits() const { return 0; }
    };
    
    struct sr_t : stmt_accept_t<sr_t>, ins_t<sr_t>
    {
      
      sr_t()
      {}
      
      sr_t(uint32_t code)
      { (void)code; }
      
      
      static uint32_t mask() { return 0b1111 << 26; }
      static uint32_t code() { return 0b1000 << 26; }
      uint32_t bits() const { return 0; }
    };
    
    struct rr_t : stmt_accept_t<rr_t>, ins_t<rr_t>
    {
      
      rr_t()
      {}
      
      rr_t(uint32_t code)
      { (void)code; }
      
      
      static uint32_t mask() { return 0b1111 << 26; }
      static uint32_t code() { return 0b1001 << 26; }
      uint32_t bits() const { return 0; }
    };
    
    struct sl_t : stmt_accept_t<sl_t>, ins_t<sl_t>
    {
      
      sl_t()
      {}
      
      sl_t(uint32_t code)
      { (void)code; }
      
      
      static uint32_t mask() { return 0b1111 << 26; }
      static uint32_t code() { return 0b1010 << 26; }
      uint32_t bits() const { return 0; }
    };
    
    struct rl_t : stmt_accept_t<rl_t>, ins_t<rl_t>
    {
      
      rl_t()
      {}
      
      rl_t(uint32_t code)
      { (void)code; }
      
      
      static uint32_t mask() { return 0b1111 << 26; }
      static uint32_t code() { return 0b1011 << 26; }
      uint32_t bits() const { return 0; }
    };
    
    struct rl8_t : stmt_accept_t<rl8_t>, ins_t<rl8_t>
    {
      
      rl8_t()
      {}
      
      rl8_t(uint32_t code)
      { (void)code; }
      
      
      static uint32_t mask() { return 0b1111 << 26; }
      static uint32_t code() { return 0b1111 << 26; }
      uint32_t bits() const { return 0; }
    };
    
    struct mov_ram_x_t : stmt_accept_t<mov_ram_x_t>, ins_t<mov_ram_x_t>
    {
      
      mov_ram_x_t(x_src_t src)
        : src(src) {}
      
      mov_ram_x_t(uint32_t code)
        : src(code) { (void)code; }
      
      const x_src_t src;
      
      static uint32_t mask() { return 0b1 << 25; }
      static uint32_t code() { return 0b1 << 25; }
      uint32_t bits() const { return src.bits(); }
    };
    
    struct mov_mul_p_t : stmt_accept_t<mov_mul_p_t>, ins_t<mov_mul_p_t>
    {
      
      mov_mul_p_t()
      {}
      
      mov_mul_p_t(uint32_t code)
      { (void)code; }
      
      
      static uint32_t mask() { return 0b11 << 23; }
      static uint32_t code() { return 0b10 << 23; }
      uint32_t bits() const { return 0; }
    };
    
    struct mov_ram_p_t : stmt_accept_t<mov_ram_p_t>, ins_t<mov_ram_p_t>
    {
      
      mov_ram_p_t(x_src_t src)
        : src(src) {}
      
      mov_ram_p_t(uint32_t code)
        : src(code) { (void)code; }
      
      const x_src_t src;
      
      static uint32_t mask() { return 0b11 << 23; }
      static uint32_t code() { return 0b11 << 23; }
      uint32_t bits() const { return src.bits(); }
    };
    
    struct mov_ram_y_t : stmt_accept_t<mov_ram_y_t>, ins_t<mov_ram_y_t>
    {
      
      mov_ram_y_t(y_src_t src)
        : src(src) {}
      
      mov_ram_y_t(uint32_t code)
        : src(code) { (void)code; }
      
      const y_src_t src;
      
      static uint32_t mask() { return 0b1 << 19; }
      static uint32_t code() { return 0b1 << 19; }
      uint32_t bits() const { return src.bits(); }
    };
    
    struct clr_a_t : stmt_accept_t<clr_a_t>, ins_t<clr_a_t>
    {
      
      clr_a_t()
      {}
      
      clr_a_t(uint32_t code)
      { (void)code; }
      
      
      static uint32_t mask() { return 0b11 << 17; }
      static uint32_t code() { return 0b01 << 17; }
      uint32_t bits() const { return 0; }
    };
    
    struct mov_alu_a_t : stmt_accept_t<mov_alu_a_t>, ins_t<mov_alu_a_t>
    {
      
      mov_alu_a_t()
      {}
      
      mov_alu_a_t(uint32_t code)
      { (void)code; }
      
      
      static uint32_t mask() { return 0b11 << 17; }
      static uint32_t code() { return 0b10 << 17; }
      uint32_t bits() const { return 0; }
    };
    
    struct mov_ram_a_t : stmt_accept_t<mov_ram_a_t>, ins_t<mov_ram_a_t>
    {
      
      mov_ram_a_t(y_src_t src)
        : src(src) {}
      
      mov_ram_a_t(uint32_t code)
        : src(code) { (void)code; }
      
      const y_src_t src;
      
      static uint32_t mask() { return 0b11 << 17; }
      static uint32_t code() { return 0b11 << 17; }
      uint32_t bits() const { return src.bits(); }
    };
    
    struct mov_imm_d1_t : stmt_accept_t<mov_imm_d1_t>, ins_imm_t<mov_imm_d1_t, 8>
    {
      using imm_type = uimm_t<8>;
      
      mov_imm_d1_t(imm_type imm, d1_dst_t dst)
        : ins_imm_t(imm), dst(dst) {}
      
      mov_imm_d1_t(uint32_t code)
        : ins_imm_t(code), dst(code) { (void)code; }
      
      const d1_dst_t dst;
      
      static uint32_t mask() { return 0b11 << 12; }
      static uint32_t code() { return 0b01 << 12; }
      uint32_t bits() const { return dst.bits(); }
    };
    
    struct mov_ram_d1_t : stmt_accept_t<mov_ram_d1_t>, ins_t<mov_ram_d1_t>
    {
      
      mov_ram_d1_t(d1_dst_t dst, d1_src_t src)
        : dst(dst), src(src) {}
      
      mov_ram_d1_t(uint32_t code)
        : dst(code), src(code) { (void)code; }
      
      const d1_dst_t dst;
      const d1_src_t src;
      
      static uint32_t mask() { return 0b11 << 12; }
      static uint32_t code() { return 0b11 << 12; }
      uint32_t bits() const { return dst.bits() | src.bits(); }
    };
    
    
  } // op
  
  namespace load {
    
    struct cond_t {
      enum value_t {
        z,
        nz,
        s,
        ns,
        c,
        nc,
        t0,
        nt0,
        zs,
        nzs,
      };
      
      const value_t value;
      
      constexpr cond_t(value_t value)
        : value(value) {}
      
      constexpr cond_t(uint32_t code)
        : value(to_value(code)) {}
      
      static constexpr uint32_t mask() { return 0b111111 << 19; }
      
      static constexpr value_t to_value(uint32_t code)
      {
        using enum value_t;
        
        switch (code & mask()) {
          case 0b100001 << 19: return z;
          case 0b000001 << 19: return nz;
          case 0b100010 << 19: return s;
          case 0b000010 << 19: return ns;
          case 0b100100 << 19: return c;
          case 0b000100 << 19: return nc;
          case 0b101000 << 19: return t0;
          case 0b001000 << 19: return nt0;
          case 0b100011 << 19: return zs;
          case 0b000011 << 19: return nzs;
          default:
            std::cerr << "invalid load cond code: " << (code & mask()) << std::endl;
            throw std::runtime_error("invalid code");
        }
      }
      
      uint32_t bits() const
      {
        using enum value_t;
        
        switch (value) {
          case z: return 0b100001 << 19;
          case nz: return 0b000001 << 19;
          case s: return 0b100010 << 19;
          case ns: return 0b000010 << 19;
          case c: return 0b100100 << 19;
          case nc: return 0b000100 << 19;
          case t0: return 0b101000 << 19;
          case nt0: return 0b001000 << 19;
          case zs: return 0b100011 << 19;
          case nzs: return 0b000011 << 19;
          default: __builtin_unreachable();
        }
      }
    };
    
    struct dst_t {
      enum value_t {
        mc0,
        mc1,
        mc2,
        mc3,
        rx,
        pl,
        ra0,
        wa0,
        lop,
        pc,
      };
      
      const value_t value;
      
      constexpr dst_t(value_t value)
        : value(value) {}
      
      constexpr dst_t(uint32_t code)
        : value(to_value(code)) {}
      
      static constexpr uint32_t mask() { return 0b1111 << 26; }
      
      static constexpr value_t to_value(uint32_t code)
      {
        using enum value_t;
        
        switch (code & mask()) {
          case 0b0000 << 26: return mc0;
          case 0b0001 << 26: return mc1;
          case 0b0010 << 26: return mc2;
          case 0b0011 << 26: return mc3;
          case 0b0100 << 26: return rx;
          case 0b0101 << 26: return pl;
          case 0b0110 << 26: return ra0;
          case 0b0111 << 26: return wa0;
          case 0b1010 << 26: return lop;
          case 0b1100 << 26: return pc;
          default:
            std::cerr << "invalid load dst code: " << (code & mask()) << std::endl;
            throw std::runtime_error("invalid code");
        }
      }
      
      uint32_t bits() const
      {
        using enum value_t;
        
        switch (value) {
          case mc0: return 0b0000 << 26;
          case mc1: return 0b0001 << 26;
          case mc2: return 0b0010 << 26;
          case mc3: return 0b0011 << 26;
          case rx: return 0b0100 << 26;
          case pl: return 0b0101 << 26;
          case ra0: return 0b0110 << 26;
          case wa0: return 0b0111 << 26;
          case lop: return 0b1010 << 26;
          case pc: return 0b1100 << 26;
          default: __builtin_unreachable();
        }
      }
    };
    
    struct mvi_t : stmt_accept_t<mvi_t>, ins_imm_t<mvi_t, 25>
    {
      using imm_type = uimm_t<25>;
      
      mvi_t(imm_type imm, dst_t dst)
        : ins_imm_t(imm), dst(dst) {}
      
      mvi_t(uint32_t code)
        : ins_imm_t(code), dst(code) { (void)code; }
      
      const dst_t dst;
      
      static uint32_t mask() { return 0b1100001 << 25; }
      static uint32_t code() { return 0b1000000 << 25; }
      uint32_t bits() const { return dst.bits(); }
    };
    
    struct mvi_cond_t : stmt_accept_t<mvi_cond_t>, ins_imm_t<mvi_cond_t, 19>
    {
      using imm_type = uimm_t<19>;
      
      mvi_cond_t(imm_type imm, dst_t dst, cond_t cond)
        : ins_imm_t(imm), dst(dst), cond(cond) {}
      
      mvi_cond_t(uint32_t code)
        : ins_imm_t(code), dst(code), cond(code) { (void)code; }
      
      const dst_t dst;
      const cond_t cond;
      
      static uint32_t mask() { return 0b1100001 << 25; }
      static uint32_t code() { return 0b1000001 << 25; }
      uint32_t bits() const { return dst.bits() | cond.bits(); }
    };
    
    
  } // load
  
  namespace dma {
    
    struct ram_t {
      enum value_t {
        m0,
        m1,
        m2,
        m3,
        mc0,
        mc1,
        mc2,
        mc3,
      };
      
      const value_t value;
      
      constexpr ram_t(value_t value)
        : value(value) {}
      
      constexpr ram_t(uint32_t code)
        : value(to_value(code)) {}
      
      static constexpr uint32_t mask() { return 0b111 << 0; }
      
      static constexpr value_t to_value(uint32_t code)
      {
        using enum value_t;
        
        switch (code & mask()) {
          case 0b000 << 0: return m0;
          case 0b001 << 0: return m1;
          case 0b010 << 0: return m2;
          case 0b011 << 0: return m3;
          case 0b100 << 0: return mc0;
          case 0b101 << 0: return mc1;
          case 0b110 << 0: return mc2;
          case 0b111 << 0: return mc3;
          default:
            std::cerr << "invalid dma ram code: " << (code & mask()) << std::endl;
            throw std::runtime_error("invalid code");
        }
      }
      
      uint32_t bits() const
      {
        using enum value_t;
        
        switch (value) {
          case m0: return 0b000 << 0;
          case m1: return 0b001 << 0;
          case m2: return 0b010 << 0;
          case m3: return 0b011 << 0;
          case mc0: return 0b100 << 0;
          case mc1: return 0b101 << 0;
          case mc2: return 0b110 << 0;
          case mc3: return 0b111 << 0;
          default: __builtin_unreachable();
        }
      }
    };
    
    struct src_t {
      enum value_t {
        mc0,
        mc1,
        mc2,
        mc3,
      };
      
      const value_t value;
      
      constexpr src_t(value_t value)
        : value(value) {}
      
      constexpr src_t(uint32_t code)
        : value(to_value(code)) {}
      
      static constexpr uint32_t mask() { return 0b111 << 8; }
      
      static constexpr value_t to_value(uint32_t code)
      {
        using enum value_t;
        
        switch (code & mask()) {
          case 0b000 << 8: return mc0;
          case 0b001 << 8: return mc1;
          case 0b010 << 8: return mc2;
          case 0b011 << 8: return mc3;
          default:
            std::cerr << "invalid dma src code: " << (code & mask()) << std::endl;
            throw std::runtime_error("invalid code");
        }
      }
      
      uint32_t bits() const
      {
        using enum value_t;
        
        switch (value) {
          case mc0: return 0b000 << 8;
          case mc1: return 0b001 << 8;
          case mc2: return 0b010 << 8;
          case mc3: return 0b011 << 8;
          default: __builtin_unreachable();
        }
      }
    };
    
    struct dst_t {
      enum value_t {
        mc0,
        mc1,
        mc2,
        mc3,
        prg,
      };
      
      const value_t value;
      
      constexpr dst_t(value_t value)
        : value(value) {}
      
      constexpr dst_t(uint32_t code)
        : value(to_value(code)) {}
      
      static constexpr uint32_t mask() { return 0b111 << 8; }
      
      static constexpr value_t to_value(uint32_t code)
      {
        using enum value_t;
        
        switch (code & mask()) {
          case 0b000 << 8: return mc0;
          case 0b001 << 8: return mc1;
          case 0b010 << 8: return mc2;
          case 0b011 << 8: return mc3;
          case 0b100 << 8: return prg;
          default:
            std::cerr << "invalid dma dst code: " << (code & mask()) << std::endl;
            throw std::runtime_error("invalid code");
        }
      }
      
      uint32_t bits() const
      {
        using enum value_t;
        
        switch (value) {
          case mc0: return 0b000 << 8;
          case mc1: return 0b001 << 8;
          case mc2: return 0b010 << 8;
          case mc3: return 0b011 << 8;
          case prg: return 0b100 << 8;
          default: __builtin_unreachable();
        }
      }
    };
    
    struct hold_t {
      enum value_t {
        _false,
        _true,
      };
      
      const value_t value;
      
      constexpr hold_t(value_t value)
        : value(value) {}
      
      constexpr hold_t(uint32_t code)
        : value(to_value(code)) {}
      
      static constexpr uint32_t mask() { return 0b1 << 14; }
      
      static constexpr value_t to_value(uint32_t code)
      {
        using enum value_t;
        
        switch (code & mask()) {
          case 0b0 << 14: return _false;
          case 0b1 << 14: return _true;
          default:
            std::cerr << "invalid dma hold code: " << (code & mask()) << std::endl;
            throw std::runtime_error("invalid code");
        }
      }
      
      uint32_t bits() const
      {
        using enum value_t;
        
        switch (value) {
          case _false: return 0b0 << 14;
          case _true: return 0b1 << 14;
          default: __builtin_unreachable();
        }
      }
    };
    
    struct add_t {
      enum value_t {
        _0,
        _1,
        _2,
        _4,
        _8,
        _16,
        _32,
        _64,
      };
      
      const value_t value;
      
      constexpr add_t(value_t value)
        : value(value) {}
      
      constexpr add_t(uint32_t code)
        : value(to_value(code)) {}
      
      static constexpr uint32_t mask() { return 0b111 << 15; }
      
      static constexpr value_t to_value(uint32_t code)
      {
        using enum value_t;
        
        switch (code & mask()) {
          case 0b000 << 15: return _0;
          case 0b001 << 15: return _1;
          case 0b010 << 15: return _2;
          case 0b011 << 15: return _4;
          case 0b100 << 15: return _8;
          case 0b101 << 15: return _16;
          case 0b110 << 15: return _32;
          case 0b111 << 15: return _64;
          default:
            std::cerr << "invalid dma add code: " << (code & mask()) << std::endl;
            throw std::runtime_error("invalid code");
        }
      }
      
      uint32_t bits() const
      {
        using enum value_t;
        
        switch (value) {
          case _0: return 0b000 << 15;
          case _1: return 0b001 << 15;
          case _2: return 0b010 << 15;
          case _4: return 0b011 << 15;
          case _8: return 0b100 << 15;
          case _16: return 0b101 << 15;
          case _32: return 0b110 << 15;
          case _64: return 0b111 << 15;
          default: __builtin_unreachable();
        }
      }
    };
    
    struct d0_dst_imm_t : stmt_accept_t<d0_dst_imm_t>, ins_imm_t<d0_dst_imm_t, 8>
    {
      using imm_type = uimm_t<8>;
      
      d0_dst_imm_t(imm_type imm, add_t add, hold_t hold, dst_t dst)
        : ins_imm_t(imm), add(add), hold(hold), dst(dst) {}
      
      d0_dst_imm_t(uint32_t code)
        : ins_imm_t(code), add(code), hold(code), dst(code) { (void)code; }
      
      const add_t add;
      const hold_t hold;
      const dst_t dst;
      
      static uint32_t mask() { return 0b11110000000000000011 << 12; }
      static uint32_t code() { return 0b11000000000000000000 << 12; }
      uint32_t bits() const { return add.bits() | hold.bits() | dst.bits(); }
    };
    
    struct src_d0_imm_t : stmt_accept_t<src_d0_imm_t>, ins_imm_t<src_d0_imm_t, 8>
    {
      using imm_type = uimm_t<8>;
      
      src_d0_imm_t(imm_type imm, add_t add, hold_t hold, src_t src)
        : ins_imm_t(imm), add(add), hold(hold), src(src) {}
      
      src_d0_imm_t(uint32_t code)
        : ins_imm_t(code), add(code), hold(code), src(code) { (void)code; }
      
      const add_t add;
      const hold_t hold;
      const src_t src;
      
      static uint32_t mask() { return 0b11110000000000000011 << 12; }
      static uint32_t code() { return 0b11000000000000000001 << 12; }
      uint32_t bits() const { return add.bits() | hold.bits() | src.bits(); }
    };
    
    struct d0_dst_ram_t : stmt_accept_t<d0_dst_ram_t>, ins_t<d0_dst_ram_t>
    {
      
      d0_dst_ram_t(add_t add, hold_t hold, dst_t dst, ram_t ram)
        : add(add), hold(hold), dst(dst), ram(ram) {}
      
      d0_dst_ram_t(uint32_t code)
        : add(code), hold(code), dst(code), ram(code) { (void)code; }
      
      const add_t add;
      const hold_t hold;
      const dst_t dst;
      const ram_t ram;
      
      static uint32_t mask() { return 0b11110000000000000011 << 12; }
      static uint32_t code() { return 0b11000000000000000010 << 12; }
      uint32_t bits() const { return add.bits() | hold.bits() | dst.bits() | ram.bits(); }
    };
    
    struct src_d0_ram_t : stmt_accept_t<src_d0_ram_t>, ins_t<src_d0_ram_t>
    {
      
      src_d0_ram_t(add_t add, hold_t hold, src_t src, ram_t ram)
        : add(add), hold(hold), src(src), ram(ram) {}
      
      src_d0_ram_t(uint32_t code)
        : add(code), hold(code), src(code), ram(code) { (void)code; }
      
      const add_t add;
      const hold_t hold;
      const src_t src;
      const ram_t ram;
      
      static uint32_t mask() { return 0b11110000000000000011 << 12; }
      static uint32_t code() { return 0b11000000000000000011 << 12; }
      uint32_t bits() const { return add.bits() | hold.bits() | src.bits() | ram.bits(); }
    };
    
    
  } // dma
  
  namespace jump {
    
    struct cond_t {
      enum value_t {
        z,
        nz,
        s,
        ns,
        c,
        nc,
        t0,
        nt0,
        zs,
        nzs,
      };
      
      const value_t value;
      
      constexpr cond_t(value_t value)
        : value(value) {}
      
      constexpr cond_t(uint32_t code)
        : value(to_value(code)) {}
      
      static constexpr uint32_t mask() { return 0b111111 << 19; }
      
      static constexpr value_t to_value(uint32_t code)
      {
        using enum value_t;
        
        switch (code & mask()) {
          case 0b100001 << 19: return z;
          case 0b000001 << 19: return nz;
          case 0b100010 << 19: return s;
          case 0b000010 << 19: return ns;
          case 0b100100 << 19: return c;
          case 0b000100 << 19: return nc;
          case 0b101000 << 19: return t0;
          case 0b001000 << 19: return nt0;
          case 0b100011 << 19: return zs;
          case 0b000011 << 19: return nzs;
          default:
            std::cerr << "invalid jump cond code: " << (code & mask()) << std::endl;
            throw std::runtime_error("invalid code");
        }
      }
      
      uint32_t bits() const
      {
        using enum value_t;
        
        switch (value) {
          case z: return 0b100001 << 19;
          case nz: return 0b000001 << 19;
          case s: return 0b100010 << 19;
          case ns: return 0b000010 << 19;
          case c: return 0b100100 << 19;
          case nc: return 0b000100 << 19;
          case t0: return 0b101000 << 19;
          case nt0: return 0b001000 << 19;
          case zs: return 0b100011 << 19;
          case nzs: return 0b000011 << 19;
          default: __builtin_unreachable();
        }
      }
    };
    
    struct jmp_t : stmt_accept_t<jmp_t>, ins_imm_t<jmp_t, 25>
    {
      using imm_type = uimm_t<25>;
      
      jmp_t(imm_type imm)
        : ins_imm_t(imm) {}
      
      jmp_t(uint32_t code)
        : ins_imm_t(code) { (void)code; }
      
      
      static uint32_t mask() { return 0b1111001 << 25; }
      static uint32_t code() { return 0b1101000 << 25; }
      uint32_t bits() const { return 0; }
    };
    
    struct jmp_cond_t : stmt_accept_t<jmp_cond_t>, ins_imm_t<jmp_cond_t, 19>
    {
      using imm_type = uimm_t<19>;
      
      jmp_cond_t(imm_type imm, cond_t cond)
        : ins_imm_t(imm), cond(cond) {}
      
      jmp_cond_t(uint32_t code)
        : ins_imm_t(code), cond(code) { (void)code; }
      
      const cond_t cond;
      
      static uint32_t mask() { return 0b1111001 << 25; }
      static uint32_t code() { return 0b1101001 << 25; }
      uint32_t bits() const { return cond.bits(); }
    };
    
    
  } // jump
  
  namespace loop {
    
    struct btm_t : stmt_accept_t<btm_t>, ins_t<btm_t>
    {
      
      btm_t()
      {}
      
      btm_t(uint32_t code)
      { (void)code; }
      
      
      static uint32_t mask() { return 0b11111 << 27; }
      static uint32_t code() { return 0b11100 << 27; }
      uint32_t bits() const { return 0; }
    };
    
    struct lps_t : stmt_accept_t<lps_t>, ins_t<lps_t>
    {
      
      lps_t()
      {}
      
      lps_t(uint32_t code)
      { (void)code; }
      
      
      static uint32_t mask() { return 0b11111 << 27; }
      static uint32_t code() { return 0b11101 << 27; }
      uint32_t bits() const { return 0; }
    };
    
    
  } // loop
  
  namespace end {
    
    struct end_t : stmt_accept_t<end_t>, ins_t<end_t>
    {
      
      end_t()
      {}
      
      end_t(uint32_t code)
      { (void)code; }
      
      
      static uint32_t mask() { return 0b11111 << 27; }
      static uint32_t code() { return 0b11110 << 27; }
      uint32_t bits() const { return 0; }
    };
    
    struct endi_t : stmt_accept_t<endi_t>, ins_t<endi_t>
    {
      
      endi_t()
      {}
      
      endi_t(uint32_t code)
      { (void)code; }
      
      
      static uint32_t mask() { return 0b11111 << 27; }
      static uint32_t code() { return 0b11111 << 27; }
      uint32_t bits() const { return 0; }
    };
    
  } // namespace end
  
} // namespace dsp

