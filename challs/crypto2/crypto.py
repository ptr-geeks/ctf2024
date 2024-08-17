alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890!@#$%^&*()_+-=[]{}|;':,.<>?/`~"
key = []

for i in range(4):
    key.append(int(input(f"Enter key {i+1}: ")))

plaintext = input("Enter data: ")
ciphertext = ""
for (i, c) in enumerate(plaintext):
    pt = alphabet.find(c)
    ct = (pt + key[i % len(key)]) % len(alphabet)
    ciphertext += alphabet[ct]

print(f"Ciphertext: {ciphertext}")
