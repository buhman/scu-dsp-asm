#include <cstdint>
#include <string_view>
#include <fstream>

#include "stmt.hpp"
#include "stmt_ins.hpp"
#include "control_word.hpp"
#include "ast_printer.hpp"

static uint32_t uint32_be(std::string_view v)
{
  return static_cast<uint8_t>(v[0]) << 24
       | static_cast<uint8_t>(v[1]) << 16
       | static_cast<uint8_t>(v[2]) << 8
       | static_cast<uint8_t>(v[3]) << 0;
}

static dsp::stmt_t * decompile(uint32_t code)
{
  using namespace dsp::op;
  using namespace dsp::load;
  using namespace dsp::dma;
  using namespace dsp::jump;
  using namespace dsp::loop;
  using namespace dsp::end;
  using namespace dsp::nop;

  if      (control_word_t::pred(code)) return new control_word_t(code);
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

static void run(std::string source)
{
  std::string_view buf(source);
  dsp::ast::printer_t printer(std::cout);

  for (decltype(buf)::size_type i = 0; i < (buf.length() / 4); i++) {
    uint32_t code = uint32_be(buf.substr(i * 4, 4));

    dsp::stmt_t * stmt = decompile(code);
    stmt->accept(&printer);
    std::cout << std::endl;
  }
}

static int run_file(char const * const input_filename)
{
  std::ifstream is {input_filename, std::ios::binary | std::ios::ate};
  if (!is.is_open()) {
    std::cerr << "failed to open " << input_filename << std::endl;
    return -1;
  }
  const std::streampos size = is.tellg();
  std::string buf(size, '\0');
  is.seekg(0);
  if (!is.read(&buf[0], size)) {
    std::cerr << "read failed" << std::endl;
    return -1;
  }

  run(buf);

  return 0;
}

int main(const int argc, char const * const argv[])
{
  const std::string c_source("-s");

  switch (argc) {
  case 2: return run_file(argv[1]);
  default:
    std::cerr << "Usage: " << argv[0] << " input-filename" << std::endl;
    return -1;
  }
}
