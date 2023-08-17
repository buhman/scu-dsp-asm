#include "lexer.hpp"
#include "token.hpp"

namespace dsp {

struct lexer_iterator_t
{
  token_t previous_token;
  token_t current_token;
  lexer_t& lexer;

  lexer_iterator_t(lexer_t& lexer)
    : lexer(lexer), previous_token(lexer.scan_token()), current_token(previous_token)
  {
  }

  token_t& advance()
  {
    previous_token = current_token;
    current_token = lexer.scan_token();
    return previous_token;
  }

  token_t& peek()
  {
    return current_token;
  }

  token_t& previous()
  {
    return previous_token;
  }
};

}
