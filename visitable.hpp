#pragma once

namespace dsp {

// expressions
struct binary_t;
struct grouping_t;
struct identifier_t;
struct literal_t;
struct unary_t;

// instructions
namespace op {
struct andl_t;
struct orl_t;
struct xorl_t;
struct add_t;
struct sub_t;
struct ad2_t;
struct sr_t;
struct rr_t;
struct sl_t;
struct rl_t;
struct rl8_t;

struct mov_ram_x_t;
struct mov_ram_x_t;
struct mov_mul_p_t;
struct mov_ram_p_t;
struct mov_ram_y_t;
struct clr_a_t;
struct mov_alu_a_t;
struct mov_ram_a_t;
struct mov_imm_d1_t;
struct mov_ram_d1_t;

struct control_word_t;
}

namespace load {
struct mvi_t;
struct mvi_cond_t;
}

namespace dma {
struct d0_dst_imm_t;
struct src_d0_imm_t;
struct d0_dst_ram_t;
struct src_d0_ram_t;
}

namespace jump {
struct jmp_t;
struct jmp_cond_t;
}

namespace loop {
struct btm_t;
struct lps_t;
}

namespace end {
struct end_t;
struct endi_t;
}

namespace nop {
struct nop_t;
}

struct assign_t;
struct label_t;

}
