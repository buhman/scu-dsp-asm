#include <iostream>
#include <fstream>
#include <string>

#include "token.hpp"

static bool had_error = false;

static void report(int line, std::string where, std::string message)
{
  std::cerr << "[line " << line << "] Error" << where << ": " << message;
  had_error = true;
}

void error(int line, std::string message)
{
  report(line, "", message);
}

static void run(std::string source)
{
  std::string_view buf {source};
  (void)buf;
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
  return had_error;
}

int main(const int argc, char const * const argv[])
{
  switch (argc) {
  case 1: run_prompt(); return had_error;
  case 2: return run_file(argv[1]);
  default:
    std::cerr << "Usage: " << argv[0] << " [filename]" << std::endl;
    return -1;
  }
}
