import sys

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
            p(inden1 + f"if (ix == s.length()) return {{ token_t::type_t::_{terminal} }};")
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
    p("inline static constexpr std::optional<enum token_t::type_t>")
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


alu_keywords = [
    "ad2",
    "add",
    "and",
    "nop",
    "or",
    "rl",
    "rl8",
    "rr",
    "sl",
    "sr",
    "sub",
    "xor",
]

x_bus_keywords = [
    "mov", # Mn, MCn
    "x",
    "p",
    "mul",
]

mn = ["m0", "m1", "m2", "m3"]
mcn = ["mc0", "mc1", "mc2", "mc3"]

y_bus_keywords = [
    "mov", # Mn, MCn
    "clr",
    "y",
    "a",
    "alu",
]

d1_bus_keywords = [
    "mov", # MCn
    "alh",
    "all",
]

reg_keywords = [
    "rx",
    "pl",
    "ra0",
    "wa0",
    "lop",
    "top",
]

cond_keywords = [
    "z",
    "nz",
    "s",
    "ns",
    "c",
    "nc",
    "t0",
    "nt0",
    "zs",
    "nzs",
]

move_immediate_keywords = [
    "mvi",
]

dma_keywords = [
    "dma",
    "dmah",
    "d0",
    "prg",
]

jmp_keywords = [
    "jmp",
]

loop_keywords = [
    "btm",
    "lps",
]

halt_keywords = [
    "end",
    "endi",
]

directive_keywords = [
    "equ",
    "org",
]

keywords = sorted(set([
    *alu_keywords,
    *x_bus_keywords,
    *mn,
    *mcn,
    *y_bus_keywords,
    *d1_bus_keywords,
    *reg_keywords,
    *cond_keywords,
    *move_immediate_keywords,
    *dma_keywords,
    *jmp_keywords,
    *loop_keywords,
    *halt_keywords,
    *directive_keywords,
]))

if sys.argv[1] == 'hpp':
    d = build_radix_tree(keywords)
    print_keyword_func(d)
elif sys.argv[1] == 'enum_inc':
    for k in keywords:
        print(f"_{k},")
elif sys.argv[1] == 'case_inc':
    for k in keywords:
        print(f'case _{k.ljust(4, " ")}       : return os << "{k.upper()}";')
else:
    assert False, sys.argv
