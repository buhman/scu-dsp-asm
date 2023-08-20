#include <stdexcept>
#include <string>
#include <vector>
#include <optional>

#include "token.hpp"
#include "expr.hpp"
#include "stmt.hpp"

namespace dsp {

struct parse_error_t : std::runtime_error
{
  parse_error_t(const std::string& msg)
    : std::runtime_error(msg)
  { }
};

struct parser_t
{
  int current_ix = 0;
  std::vector<token_t> tokens;

  parser_t(const std::vector<token_t>& tokens)
    : tokens(tokens)
  { }

  static parse_error_t error(const token_t& token, const std::string message);

  bool at_end_p();

  const token_t& previous();
  const token_t& peek();
  const token_t& advance();
  bool check(enum token_t::type_t token_type);
  bool match(enum token_t::type_t token_type);
  template <typename... Targs>
  bool match(enum token_t::type_t token_type, Targs... args);
  token_t consume(enum token_t::type_t token_type, const std::string error_message);

  expr_t * expression();
  expr_t * term();
  expr_t * factor();
  expr_t * unary();
  expr_t * shift();
  expr_t * andl();
  expr_t * orl();
  expr_t * primary();

  std::optional<op::op_t *> alu();
  bool xyd1_src();
  std::optional<op::d1_dest_t> d1_dest();
  std::optional<op::op_t *> xyd1_bus();
  std::optional<stmt_t *> op();
  load::dest_t load_dest();
  load::cond_t load_cond();
  std::optional<stmt_t *> load();
  dma::src_t dma_src();
  dma::dst_t dma_dst();
  std::optional<dma::length_ram_t> dma_length_ram();
  std::optional<stmt_t *> dma();
  std::optional<stmt_t *> jump();
  std::optional<stmt_t *> loop();
  std::optional<stmt_t *> end();
  std::optional<stmt_t *> instruction();
  std::optional<stmt_t *> instruction_statement();
  stmt_t * statement();
};

}
