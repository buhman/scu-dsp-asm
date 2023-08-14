#pragma once

#include <iostream>

namespace dsp {

extern bool had_error;

static inline void report(const int line, const int col, const std::string where, const std::string message)
{
  std::cerr << "[line " << line
            << " col " << col
            << "] error" << where << ": " << message
            << std::endl;

  had_error = true;
}

static inline void error(const int line,  const int col, std::string message)
{
  report(line, col, "", message);
}

}
