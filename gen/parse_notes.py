import csv
import sys
from dataclasses import dataclass
from typing import Union

class _X:
    def __repr__(self):
        return 'x'

X = _X()

bit = Union[int, _X]

@dataclass
class Bits:
    bits: tuple[bit, bit, bit, bit, bit, bit, bit, bit,
                bit, bit, bit, bit, bit, bit, bit, bit,
                bit, bit, bit, bit, bit, bit, bit, bit,
                bit, bit, bit, bit, bit, bit, bit, bit]

    def __repr__(self):
        return ''.join(repr(i) for i in self.bits)

    def __getitem__(self, key):
        return list(reversed(self.bits))[key]

@dataclass
class Const:
    name: str
    bits: Bits

@dataclass
class Enum:
    name: str
    consts: list[Const]

@dataclass
class Struct:
    name: str
    bits: Bits
    fields: list[tuple[int, str]]

@dataclass
class Namespace:
    name: str

def read(path):
    with open(path, newline='') as f:
        reader = csv.reader(f, delimiter=',', quotechar='"')
        return list(reader)

label_col = 2
bits_col = 3

def parse_struct(rows, ix):
    return None, ix + 1

def validate_consts(consts):
    by_index = set([
        frozenset([ix for ix, bit in enumerate(const.bits) if bit is not X])
        for const in consts
    ])
    assert len(by_index) == 1

def get_bits(row):
    return [
        int(i) if i in {"0", "1"} else X
        for i in row[bits_col:bits_col+32]
    ]

def get_nonbits(row):
    return [
        (31-ix, i)
        for ix, i in enumerate(row[bits_col:bits_col+32])
        if i and i not in {"0", "1"}
    ]

def get_name(row, key):
    label0 = row[label_col]
    assert label0.startswith(f'{key} '), label0
    _, name = label0.split(' ', maxsplit=1)
    return name

def parse_enum(rows, ix):
    enum_name = get_name(rows[ix], "enum")
    ix += 1
    consts = []

    while ix < len(rows):
        label = rows[ix][label_col]
        if not label or ' ' in label:
            validate_consts(consts)
            return Enum(enum_name, consts), ix
        else:
            const_name = label
            bits = get_bits(rows[ix])
            assert len(bits) == 32
            consts.append(Const(const_name, Bits(bits)))
            ix += 1

def parse_struct(rows, ix):
    struct_name = get_name(rows[ix], "struct")
    bits = get_bits(rows[ix])
    fields = get_nonbits(rows[ix])
    ix += 1

    struct = Struct(struct_name, Bits(bits), fields)
    return struct, ix

def parse(rows):
    ix = 0
    while ix < len(rows):
        if rows[ix][0].strip():
            yield Namespace(rows[ix][0].lower())

        label = rows[ix][label_col]
        if   label.startswith('struct'):
            ret, ix = parse_struct(rows, ix)
            yield ret
        elif label.startswith('enum'  ):
            ret, ix = parse_enum(rows, ix)
            yield ret
        else:
            ix += 1

#events = list(parse(read(sys.argv[1])))
#from pprint import pprint
#pprint(events)
