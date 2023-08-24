import sys
import struct

with open(sys.argv[1], 'rb') as f:
    b = f.read()

assert len(b) % 4 == 0, len(b)

for i in range(len(b) // 4):
    word = b[i*4:i*4+4]
    n, = struct.unpack('>I', word)
    print(f'{n:>032b}')
