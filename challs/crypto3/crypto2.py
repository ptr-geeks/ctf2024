import Crypto.Util.number as number
import Crypto.PublicKey.RSA as RSA

flag = input("Enter the flag: ")
if len(flag) > 32:
    print("Flag too long")
    exit()
flag = flag.encode('utf-8')
flag = number.bytes_to_long(flag)

key = RSA.generate(2048, e=3)
ct = pow(flag, key.e, key.n)

print("Pub key:", (key.n, key.e))
print("Cipher text:", ct)
