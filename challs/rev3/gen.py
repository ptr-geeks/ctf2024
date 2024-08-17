flag = "ptr{s0lv3D_yoUr_f1rs7_cR4ckm3}"

flag = [ord(c) for c in flag]
flag = [((c >> 4) & 0x0f) | ((c << 4) & 0xf0) for c in flag]
flag = [c ^ 0x55 for c in flag]
flag = flag[::-1]

print(len(flag), flag)
