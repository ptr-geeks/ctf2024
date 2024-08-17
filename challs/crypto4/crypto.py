import Crypto.Util.number as number

def genkey():
    p = number.getPrime(512)
    q = number.getPrime(512)
    n = p * q
    return n

e = 3
key1 = genkey()
key2 = genkey()
key3 = genkey()

flag = input("Enter the flag: ")
flag = flag.encode("utf-8")
flag = number.bytes_to_long(flag)

c1 = pow(flag, e, key1)
c2 = pow(flag, e, key2)
c3 = pow(flag, e, key3)

print(f"key1 = {key1}")
print(f"key2 = {key2}")
print(f"key3 = {key3}")
print(f"c1 = {c1}")
print(f"c2 = {c2}")
print(f"c3 = {c3}")
