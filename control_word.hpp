#pragma once

#include <cstdint>
#include <variant>
#include <vector>
#include <utility>

#include "stmt_base.hpp"
#include "stmt_ins.hpp"
#include "ins.hpp"

namespace dsp {

namespace op {
using op_t = std::variant<andl_t,
                          orl_t,
                          xorl_t,
                          add_t,
                          sub_t,
                          ad2_t,
                          sr_t,
                          rr_t,
                          sl_t,
                          rl_t,
                          rl8_t,
                          mov_ram_x_t,
                          mov_mul_p_t,
                          mov_ram_p_t,
                          mov_ram_y_t,
                          clr_a_t,
                          mov_alu_a_t,
                          mov_ram_a_t,
                          mov_imm_d1_t,
                          mov_ram_d1_t>;

struct control_word_t : stmt_accept_t<control_word_t>, ins_t<control_word_t>
{
  control_word_t(std::vector<op_t> ops)
    : ops(ops)
  {
  }

  std::vector<op_t> build_ops(uint32_t code)
  {
    std::vector<op_t> ops;
    if (andl_t::pred(code)) ops.emplace_back(op_t{std::in_place_type<andl_t>, code});
    if (orl_t::pred(code)) ops.emplace_back(op_t{std::in_place_type<orl_t>, code});
    if (xorl_t::pred(code)) ops.emplace_back(op_t{std::in_place_type<xorl_t>, code});
    if (add_t::pred(code)) ops.emplace_back(op_t{std::in_place_type<add_t>, code});
    if (sub_t::pred(code)) ops.emplace_back(op_t{std::in_place_type<sub_t>, code});
    if (ad2_t::pred(code)) ops.emplace_back(op_t{std::in_place_type<ad2_t>, code});
    if (sr_t::pred(code)) ops.emplace_back(op_t{std::in_place_type<sr_t>, code});
    if (rr_t::pred(code)) ops.emplace_back(op_t{std::in_place_type<rr_t>, code});
    if (sl_t::pred(code)) ops.emplace_back(op_t{std::in_place_type<sl_t>, code});
    if (rl_t::pred(code)) ops.emplace_back(op_t{std::in_place_type<rl_t>, code});
    if (rl8_t::pred(code)) ops.emplace_back(op_t{std::in_place_type<rl8_t>, code});
    if (mov_ram_x_t::pred(code)) ops.emplace_back(op_t{std::in_place_type<mov_ram_x_t>, code});
    if (mov_mul_p_t::pred(code)) ops.emplace_back(op_t{std::in_place_type<mov_mul_p_t>, code});
    if (mov_ram_p_t::pred(code)) ops.emplace_back(op_t{std::in_place_type<mov_ram_p_t>, code});
    if (mov_ram_y_t::pred(code)) ops.emplace_back(op_t{std::in_place_type<mov_ram_y_t>, code});
    if (clr_a_t::pred(code)) ops.emplace_back(op_t{std::in_place_type<clr_a_t>, code});
    if (mov_alu_a_t::pred(code)) ops.emplace_back(op_t{std::in_place_type<mov_alu_a_t>, code});
    if (mov_ram_a_t::pred(code)) ops.emplace_back(op_t{std::in_place_type<mov_ram_a_t>, code});
    if (mov_imm_d1_t::pred(code)) ops.emplace_back(op_t{std::in_place_type<mov_imm_d1_t>, code});
    if (mov_ram_d1_t::pred(code)) ops.emplace_back(op_t{std::in_place_type<mov_ram_d1_t>, code});

    return ops;
  }
  
  control_word_t(uint32_t code)
    : ops(build_ops(code)) {}

  const std::vector<op_t> ops;

  static constexpr uint32_t mask() { return 0b11 << 30; }
  static constexpr uint32_t code() { return 0b00 << 30; }
  static constexpr uint32_t bits() { return 0; }
};

}

}
