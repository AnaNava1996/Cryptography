from Crypto.Cipher import DES
from Crypto import Random
from PIL import Image

with open("twitter.bmp", "rb") as imageFile:
  f = imageFile.read(138)
  b = bytearray(f)
  a = imageFile.read(1442910) #a = imageFile.read(363049472) para la del pinguino
  plaintext = bytearray(a)
imageFile.close()

key = b'Eight888'
iv = Random.new().read(DES.block_size)
cipher = DES.new(key, DES.MODE_OFB, iv)
msg = iv + cipher.encrypt(plaintext)

with open("DES-OFB-encrypt.bmp","ab") as f3:
    f3.write(b)
    f3.write(msg)
    f3.close()



'''

from Crypto.Cipher import DES
from PIL import Image

with open("twitter.bmp", "rb") as imageFile:
  f = imageFile.read(138)
  b = bytearray(f)
  a = imageFile.read(1442910) #a = imageFile.read(363049472) para la del pinguino
imageFile.close()

key = b'Asegurar'
cipher =  DES.new(key, DES.MODE_OFB)
plaintext = a
msg = cipher.iv + cipher.encrypt(plaintext)

with open("DES-OFB-encrypt.bmp","ab") as f2:
    f2.write(b)
    f2.write(msg)
    f2.close()
'''
