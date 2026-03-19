from Crypto.Cipher import AES
import os

data = os.urandom(1000)
key = b'1234567890123456'
iv = b'0000000000000000'

def test_mode(mode):
    cipher = AES.new(key, mode, iv) if mode != AES.MODE_ECB else AES.new(key, mode)
    ct = cipher.encrypt(data[:len(data)//16*16])

    corrupted = bytearray(ct)
    corrupted[25] ^= 1

    cipher2 = AES.new(key, mode, iv) if mode != AES.MODE_ECB else AES.new(key, mode)
    pt = cipher2.decrypt(bytes(corrupted))

    return sum(a != b for a, b in zip(data, pt))

print("ECB:", test_mode(AES.MODE_ECB))
print("CBC:", test_mode(AES.MODE_CBC))
print("CFB:", test_mode(AES.MODE_CFB))
print("OFB:", test_mode(AES.MODE_OFB))
