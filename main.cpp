#include <iostream>
#include <fstream>
#include <string>
#include <optional>
#include <bitset>

#include "lexer.hpp"
#include "token.hpp"
#include "ast_printer.hpp"
#include "ast_resolver.hpp"
#include "ast_emitter.hpp"
#include "parser.hpp"

namespace dsp {

bool had_error = false;

}

static void run(std::string source)
{
  using namespace dsp;

  std::string_view buf(source);
  lexer_t lexer(buf);
  std::vector<token_t> tokens = lexer.lex_tokens();
  parser_t pass1(tokens);
  parser_t pass2(tokens);
  ast::printer_t printer(std::cout);
  ast::pc_t pc;
  ast::addresses_t addresses;
  ast::resolver_t resolver(pc, addresses);
  while (auto stmt_o = pass1.statement()) {
    (*stmt_o)->accept(&printer);
    std::cout << std::endl << std::flush;
    (*stmt_o)->accept(&resolver);
  }
  ast::variables_t variables;
  ast::emitter_t emitter(variables, addresses);
  while (auto stmt_o = pass2.statement()) {
    uint32_t output = (*stmt_o)->accept(&emitter);
    if (output != 0xffff'ffff) {
      std::cout << std::bitset<32>(output) << std::endl;
    }
  }
}

static void run_prompt()
{
  constexpr auto prompt = "> ";
  std::string line;
  std::cout << prompt << std::flush;
  while (std::getline(std::cin, line)) {
    run(line);
    std::cout << prompt << std::flush;
  }
}

static int run_file(char const * const filename)
{
  std::ifstream is {filename, std::ios::binary | std::ios::ate};
  if (!is.is_open()) {
    std::cerr << "failed to open " << filename << std::endl;
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
  return dsp::had_error;
}

int main(const int argc, char const * const argv[])
{
  switch (argc) {
  case 1: run_prompt(); return dsp::had_error;
  case 2: return run_file(argv[1]);
  default:
    std::cerr << "Usage: " << argv[0] << " [filename]" << std::endl;
    return -1;
  }
}
