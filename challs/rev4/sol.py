from pwn import *
import os

os.system('./sol')

#p = process('./chall')
p = remote('localhost', 1337)
p.interactive()
