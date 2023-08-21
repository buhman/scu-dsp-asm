#pragma once

#include <string_view>
#include <unordered_map>

namespace dsp {

namespace ast {

using addresses_t = std::unordered_map<std::string_view, uint32_t>;
using variables_t = std::unordered_map<std::string_view, uint32_t>;

}

}
