from Crypto.Cipher import DES
from PIL import Image

with open("twitter.bmp", "rb") as imageFile:
  f = imageFile.read(138)
  b = bytearray(f)
  a = imageFile.read(1442910) #a = imageFile.read(363049472) para la del pinguino
imageFile.close()

key = b'Asegurar'
cipher =  DES.new(key, DES.MODE_CFB)
plaintext = a
msg = cipher.iv + cipher.encrypt(plaintext)

with open("DES_CFB_encrypt.bmp","ab") as f2:
    f2.write(b)
    f2.write(msg)
f2.close()
