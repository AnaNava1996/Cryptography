from Crypto.Cipher import AES
from PIL import Image


with open("AES_OFB_encrypt.bmp", "rb") as imageFile:
  f = imageFile.read(138)
  b = bytearray(f)
  a = imageFile.read(1442910) #a = imageFile.read(363049472) para la del pinguino
imageFile.close()

key = b'AsegurarAsegurar'
cipher =  AES.new(key, AES.MODE_OFB, nonce=nonce)
msg = cipher.decrypt(a)

with open("AES_OFB_decrypt.bmp","ab") as f3:
    f3.write(b)
    f3.write(msg)
f3.close()
