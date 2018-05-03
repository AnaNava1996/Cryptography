from Crypto.Cipher import DES
from PIL import Image

with open("DES_CFB_encrypt.bmp", "rb") as imageFile:
  f = imageFile.read(138)
  b = bytearray(f)
  a = imageFile.read(1442910) #a = imageFile.read(363049472) para la del pinguino
imageFile.close()

key = b'Asegurar'
cipher =  DES.new(key, DES.MODE_CFB)
msg = cipher.decrypt(a)

with open("DES_CFB_decrypt.bmp","ab") as f3:
    f3.write(b)
    f3.write(msg)
f3.close()
