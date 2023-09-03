#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <array>
#include <iomanip>

#include "lexer.hpp"
#include "token.hpp"
#include "ast_printer.hpp"
#include "ast_resolver.hpp"
#include "ast_emitter.hpp"
#include "parser.hpp"

namespace dsp {

bool had_error = false;

}

template <typename T>
static std::array<T, 4> uint32_be(uint32_t v)
{
  return {
    static_cast<T>((v >> 24) & 0xff),
    static_cast<T>((v >> 16) & 0xff),
    static_cast<T>((v >> 8 ) & 0xff),
    static_cast<T>((v >> 0 ) & 0xff),
  };
}

static void write_hex(std::ostream& os, uint32_t v)
{
  const auto out = uint32_be<int>(v);
  os << std::setfill('0') << std::right << std::hex
     << "0x"
     << std::setw(2) << out[0]
     << std::setw(2) << out[1]
     << std::setw(2) << out[2]
     << std::setw(2) << out[3] << ',' << std::endl;
}

static void write_raw(std::ostream& os, uint32_t v)
{
  const auto out = uint32_be<char>(v);
  os.write(out.data(), 4);
}

static void run(std::ostream& os, std::string source, bool hex_output, bool verbose)
{
  using namespace dsp;

  std::string_view buf(source);
  lexer_t lexer(buf);
  std::vector<token_t> tokens = lexer.lex_tokens();
  parser_t pass1(tokens);
  parser_t pass2(tokens);
  ast::printer_t printer(std::cout);
  ast::pc_t pc;
  ast::variables_t variables;
  ast::resolver_t resolver(pc, variables);
  while (auto stmt_o = pass1.statement()) {
    if (verbose) {
      (*stmt_o)->accept(&printer);
      std::cout << std::endl << std::flush;
    }
    (*stmt_o)->accept(&resolver);
  }
  ast::emitter_t emitter(variables);
  while (auto stmt_o = pass2.statement()) {
    uint32_t output = (*stmt_o)->accept(&emitter);
    if (output != 0xffff'ffff) {
      if (hex_output) write_hex(os, output);
      else            write_raw(os, output);
    }
  }
}

static void run_prompt()
{
  constexpr auto prompt = "> ";
  std::string line;
  std::cout << prompt << std::flush;
  while (std::getline(std::cin, line)) {
    run(std::cout, line, true, true);
    std::cout << prompt << std::flush;
  }
}

static int run_file(char const * const input_filename, char const * const output_filename, bool hex_output)
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

  std::ostringstream os;
  run(os, buf, hex_output, false);

  if (!dsp::had_error) {
    std::ofstream ofs {output_filename, std::ios::binary | std::ios::trunc};
    if (!ofs.is_open()) {
      std::cerr << "failed to open " << output_filename << std::endl;
      return -1;
    }
    ofs << os.str();
  }

  return dsp::had_error;
}

int main(const int argc, char const * const argv[])
{
  const std::string c_source("-s");

  switch (argc) {
  case 1: run_prompt(); return dsp::had_error;
  case 3: return run_file(argv[1], argv[2], false);
  case 4:
    if (c_source.compare(argv[1]) == 0) return run_file(argv[2], argv[3], true);
    else
      [[fallthrough]];
  default:
    std::cerr << "Usage: " << argv[0] << " [[-s] input-filename output-filename]" << std::endl;
    return -1;
  }
}
