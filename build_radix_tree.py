def build_radix_tree(ops: list[str]) -> dict:
    root = dict()
    for op in ops:
        d = root
        for i in range(len(op)):
            if op[i] not in d:
                d[op[i]] = (None,{})
            if i == (len(op) - 1):
                d[op[i]] = (op,d[op[i]][1])
            else:
                d = d[op[i]][1]
    return root

def indent(i):
    return " " * (2 * i)

def print_switch(d, level=0):
    p = print
    inden0 = indent(level+0)
    inden1 = indent(level+1)
    inden2 = indent(level+2)
    p(inden0 + "switch (s[ix++]) {")
    for key, (terminal, children) in d.items():
        if key.upper() != key.lower():
            p(inden0 + f"case '{key.upper()}': [[fallthrough]];")
        p(inden0 + f"case '{key.lower()}':")
        if terminal is not None:
            p(inden1 + f"if (ix == s.length()) return {{ token::type_t::_{terminal} }};")
            if children:
                p(inden1 + "else {")
        else:
            if children:
                p(inden1 + "if (ix < s.length()) {")
        if children:
            print_switch(children, level+2)
            p(inden1 + "}")
        p(inden1 + "break;")
    p(inden0 + "}")

def print_keyword_func(root):
    p = print
    inden1 = indent(1)
    p("#include <optional>")
    p('#include "token.hpp"')
    p()
    p("namespace dsp {")
    p()
    p("struct keyword {")
    p()
    p("inline static constexpr std::optional<enum token::type_t>")
    p("find(const std::string_view s)")
    p("{")
    p(inden1 + "if (s.length() == 0) { return {}; }")
    p()
    p(inden1 + "std::string_view::size_type ix = 0;")
    p()
    print_switch(root, level=1)
    p(inden1 + "return {};")
    p("}")
    p()
    p("};")
    p()
    p("}")

from pprint import pprint
d = build_radix_tree([
    "alh",
    "all",
    "alu",
    "m0",  "m1",  "m2", "m3",
    "mc0", "mc1", "mc2", "mc3",
    "mul",
    "nop",
    "and",
    "or",
    "xor",
    "add",
    "sub",
    "ad2",
    "sr",
    "rr",
    "sl",
    "rl",
    "rl8",
    "clr",
    "mov",
    "mvi",
    "dma",
    "dmah",
    "jmp",
    "btm",
    "lps",
    "end",
    "endi",
    "equ",
    "org",
    "ends",
])
print_keyword_func(d)
