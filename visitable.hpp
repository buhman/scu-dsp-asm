#pragma once

namespace dsp {

// expressions
struct binary_t;
struct grouping_t;
struct literal_t;
struct unary_t;
struct assign_t;

// instructions
namespace op {
struct alu_t;
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

namespace load{
struct mvi_t;
struct mvi_cond_t;
}

namespace dma {
struct src_d0_imm_t;
struct d0_dst_imm_t;
struct src_d0_ram_t;
struct d0_dst_ram_t;
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
