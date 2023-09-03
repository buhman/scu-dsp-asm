import sys
from generate import renderer
from parse_notes import parse, read, X, Bits, Enum, Struct, Namespace

def bits_mask_literal(bits, start, end) -> str:
    b_str = lambda b: '1' if b is not X else '0'
    s = ''.join(map(b_str, reversed(bits[start:end])))
    return s

def bits_literal(bits, start, end) -> str:
    b_str = lambda b: str(b) if b is not X else '0'
    s = ''.join(map(b_str, reversed(bits[start:end])))
    return s

def bits_start_end(bits):
    start = 0
    while bits[start] is X:
        start += 1

    ix = start + 1
    end = ix
    while ix < 32:
        if bits[ix] is not X:
            end = ix + 1
        ix += 1

    return start, end

def bits_to_shift(bits) -> str:
    start, end = bits_start_end(bits)
    literal = bits_literal(bits, start, end)
    return f"0b{literal} << {start}"

def bits_to_mask(bits) -> str:
    start, end = bits_start_end(bits)
    mask = bits_mask_literal(bits, start, end)
    return f"0b{mask} << {start}"

def enum_consts_to_value(namespace_name, enum_name, consts):
    yield "static constexpr value_t to_value(uint32_t code)"
    yield "{"
    yield "using enum value_t;"
    yield ""
    yield "switch (code & mask()) {"
    for const in consts:
        shift = bits_to_shift(const.bits)
        yield f"case {shift}: return {const.name};"
    yield "default:"
    yield f'  std::cerr << "invalid {namespace_name} {enum_name} code: " << (code & mask()) << std::endl;'
    yield '  throw std::runtime_error("invalid code");'
    yield "}"
    yield "}"

def enum_consts_bits(consts):
    yield "uint32_t bits() const"
    yield "{"
    yield "using enum value_t;"
    yield ""
    yield "switch (value) {"
    for const in consts:
        shift = bits_to_shift(const.bits)
        yield f"case {const.name}: return {shift};"
    yield "default: __builtin_unreachable();"
    yield "}"
    yield "}"

def enum_value_t(consts):
    yield "enum value_t {"
    for const in consts:
        yield f"{const.name},"
    yield "};"

def enum_struct(namespace, enum):
    yield f"struct {enum.name}_t {{"
    yield from enum_value_t(enum.consts)
    yield ""
    yield "const value_t value;"
    yield ""
    yield f"constexpr {enum.name}_t(value_t value)"
    yield "  : value(value) {}"
    yield ""
    yield f"constexpr {enum.name}_t(uint32_t code)"
    yield "  : value(to_value(code)) {}"
    yield ""
    mask = bits_to_mask(enum.consts[0].bits)
    yield f"static constexpr uint32_t mask() {{ return {mask}; }}"
    yield ""
    yield from enum_consts_to_value(namespace.name, enum.name, enum.consts)
    yield ""
    yield from enum_consts_bits(enum.consts)
    yield "};"

def has_imm(struct):
    return 'imm' in {name for _i, name in struct.fields}

def imm_length(struct):
    imm_length, = [i for i, name in struct.fields if name == 'imm']
    return imm_length + 1

def f_name(name):
    return name.split('_', maxsplit=1)[-1]

def struct_struct(namespace, struct):
    if has_imm(struct):
        length = imm_length(struct)
        yield f"struct {struct.name}_t : stmt_accept_t<{struct.name}_t>, ins_imm_t<{struct.name}_t, {length}>"
        yield "{"
        yield f"using imm_type = uimm_t<{length}>;"
    else:
        yield f"struct {struct.name}_t : stmt_accept_t<{struct.name}_t>, ins_t<{struct.name}_t>"
        yield "{"
    yield ""


    field_decls = [f"{name}_t {f_name(name)}" for _, name in struct.fields if name != 'imm']
    field_inits = [f"{f_name(name)}({f_name(name)})" for _, name in struct.fields if name != 'imm']
    if has_imm(struct):
        field_decls.insert(0, "imm_type imm")
        field_inits.insert(0, "ins_imm_t(imm)")
    field_inits = ", ".join(field_inits)
    field_decls = ", ".join(field_decls)
    yield f"{struct.name}_t({field_decls})"
    if field_inits.strip():
        yield f"  : {field_inits} {{}}"
    else:
        yield "{}"
    yield ""
    yield f"{struct.name}_t(uint32_t code)"
    code_inits = [f"{f_name(name)}(code)" for _, name in struct.fields if name != 'imm']
    if has_imm(struct):
        code_inits.insert(0, "ins_imm_t(code)")
    code_inits = ", ".join(code_inits)
    if code_inits.strip():
        yield f"  : {code_inits} {{ (void)code; }}"
    else:
        yield "{ (void)code; }"
    yield ""

    for _, name in struct.fields:
        if name == 'imm':
            pass
        else:
            yield f"const {name}_t {f_name(name)};"
    yield ""

    start, end = bits_start_end(struct.bits)
    mask_literal = bits_mask_literal(struct.bits, start, end)
    literal = bits_literal(struct.bits, start, end)

    yield f"static uint32_t mask() {{ return 0b{mask_literal} << {start}; }}"
    yield f"static uint32_t code() {{ return 0b{literal} << {start}; }}"
    bits_return = " | ".join(f"{f_name(name)}.bits()" for _, name in struct.fields if name != 'imm')
    if not bits_return.strip():
        bits_return = "0"
    yield f"uint32_t bits() const {{ return {bits_return}; }}"

    yield "};"

def sort_events(events):
    enums = []
    structs = []
    namespace = None
    def do_yield():
        nonlocal enums, structs, namespace

        yield namespace
        #yield from sorted(enums, key=lambda e: e.name)
        yield from enums
        assert structs, structs
        yield from structs
        #yield from sorted(structs, key=lambda e: e.name)

    for event in events:
        if type(event) is Namespace:
            if namespace is not None:
                yield from do_yield()
            else:
                assert not enums
                assert not structs
            namespace = event
            enums = []
            structs = []
        elif type(event) is Enum:
            assert namespace is not None
            enums.append(event)
        elif type(event) is Struct:
            assert namespace is not None
            structs.append(event)
        else:
            assert False
    assert namespace is not None
    yield from do_yield()

def generate_header_namespaces(events):
    namespace = None
    yield "namespace dsp {"
    for event in events:
        if type(event) is Namespace:
            if namespace is not None:
                yield ""
                yield f"}} // {namespace.name}"
                yield ""
            yield f"namespace {event.name} {{"
            yield ""
            namespace = event
        elif type(event) is Enum:
            yield from enum_struct(namespace, event)
            yield ""
        elif type(event) is Struct:
            yield from struct_struct(namespace, event)
            yield ""
        else:
            assert False
    assert namespace is not None
    yield f"}} // namespace {namespace.name}"
    yield ""
    yield "} // namespace dsp"

def generate_includes():
    yield "#pragma once"
    yield ""
    yield "#include <cstdint>"
    yield "#include <iostream>"
    yield ""
    yield '#include "imm.hpp"'
    yield '#include "ins.hpp"'
    yield '#include "stmt_base.hpp"'
    yield ""

def generate_header():
    events = list(sort_events(parse(read(sys.argv[1]))))
    render, out = renderer()
    render(generate_includes())
    render(generate_header_namespaces(events))
    return out

print(generate_header().getvalue())

#consts=[Const(name='z', bits=xxxxxxx100001xxxxxxxxxxxxxxxxxxx),

b = Bits(bits=[X,X,1,1,0,0,X,X,X,X,X,X,X,X,X,X,X,X,X,X,X,X,X,X,X,X,X,X,X,X,X,X])
