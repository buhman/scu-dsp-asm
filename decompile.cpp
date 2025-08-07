#include "control_word.hpp"
#include "decompile.hpp"

dsp::stmt_t * decompile(uint32_t code)
{
  using namespace dsp::op;
  using namespace dsp::load;
  using namespace dsp::dma;
  using namespace dsp::jump;
  using namespace dsp::loop;
  using namespace dsp::end;
  using namespace dsp::nop;

  if      (nop_t::pred(code))          return new nop_t(code);
  else if (control_word_t::pred(code)) return new control_word_t(code);
  else if (mvi_t::pred(code))          return new mvi_t(code);
  else if (mvi_cond_t::pred(code))     return new mvi_cond_t(code);
  else if (d0_dst_imm_t::pred(code))   return new d0_dst_imm_t(code);
  else if (src_d0_imm_t::pred(code))   return new src_d0_imm_t(code);
  else if (d0_dst_ram_t::pred(code))   return new d0_dst_ram_t(code);
  else if (src_d0_ram_t::pred(code))   return new src_d0_ram_t(code);
  else if (jmp_t::pred(code))          return new jmp_t(code);
  else if (jmp_cond_t::pred(code))     return new jmp_cond_t(code);
  else if (btm_t::pred(code))          return new btm_t(code);
  else if (lps_t::pred(code))          return new lps_t(code);
  else if (end_t::pred(code))          return new end_t(code);
  else if (endi_t::pred(code))         return new endi_t(code);
  else
    throw std::runtime_error("undefined code");
}
