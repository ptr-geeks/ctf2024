import Crypto.Util.number as number

flag = input("Enter the flag: ")
flag = flag.encode('utf-8')
flag = number.bytes_to_long(flag)

p = number.getPrime(512)
q = number.getPrime(512)
n = p*q

e1 = 65537
e2 = 3

ct1 = pow(flag, e1, n)
ct2 = pow(flag, e2, n)

print(f"n = {n}")
print(f"e1 = {e1}")
print(f"e2 = {e2}")
print(f"ct1 = {ct1}")
print(f"ct2 = {ct2}")
