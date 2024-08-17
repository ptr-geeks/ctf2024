from base64 import b64encode

data = b'\xa2\xaa\xa6\xb4\x9a*\xaa\xe4\xfc\xcc$\xaa\xfc\xa4\xea\x80\xa6,\x88\x8a\xb8'
data = [x ^ 0x42 for x in data]
data = [x >> 1 for x in data]
data = bytes(data)
print(data)
print(b64encode(data))

