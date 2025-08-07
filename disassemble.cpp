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
  switch (argc) {
  case 2: return run_file(argv[1]);
  default:
    std::cerr << "Usage: " << argv[0] << " input-filename" << std::endl;
    return -1;
  }
}
