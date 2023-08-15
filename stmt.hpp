
struct assign_t : stmt_accept_t<assign_t>
{
  assign_t(token_t name, expr_t * value)
    : name(name), value(value) {}

  const token_t name;
  const expr_t * value;
};
