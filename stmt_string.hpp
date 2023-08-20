#pragma once

#include <string>

namespace dsp {

namespace op {

extern const std::string alu_type_string[];
extern const std::string xy_src_string[];
extern const std::string d1_dest_string[];
extern const std::string d1_src_string[];

}

namespace load {

extern const std::string dest_string[];
extern const std::string cond_string[];

} // load

namespace dma {

extern const std::string hold_mode_string[];
extern const std::string add_mode_string[];
extern const std::string src_string[];
extern const std::string dst_string[];
extern const std::string length_ram_string[];

} // dma

namespace jump {

extern const std::string cond_string[];

}

}
