ciphertext = "1cx]YSz)bS{u/BonYMXxrMlSPa{~-u."
alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890!@#$%^&*()_+-=[]{}|;':,.<>?/`~"

key = []
for i, c in enumerate("ptr{"):
    k = alphabet.index(ciphertext[i]) - alphabet.index(c)
    if k < 0:
        k += len(alphabet)
    key.append(k)

print(key)
key = [-k for k in key]

plaintext = ""
for (i, c) in enumerate(ciphertext):
    ct = alphabet.find(c)
    pt = (ct + key[i % len(key)]) % len(alphabet)
    plaintext += alphabet[pt]

print(plaintext)

