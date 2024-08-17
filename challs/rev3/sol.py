data = [130, 102, 131, 227, 99, 22, 112, 99, 160, 38, 98, 114, 70, 51, 160, 114, 0, 163, 194, 160, 17, 102, 50, 147, 86, 98, 226, 114, 18, 82]

data = data[::-1]
data = [d ^ 0x55 for d in data]
data = [((c >> 4) & 0x0f) | ((c << 4) & 0xf0) for c in data]

print(''.join([chr(c) for c in data]))
