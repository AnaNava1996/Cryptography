from Crypto.Cipher import DES
from Crypto import Random
from PIL import Image

with open("DES-OFB-encrypt.bmp", "rb") as imageFile:
  f = imageFile.read(138)
  b = bytearray(f)
  a = imageFile.read(1442910) #a = imageFile.read(363049472) para la del pinguino
  plaintext = bytearray(a)
imageFile.close()

key = b'Eight888'
decCipher = DES.new(key, DES.MODE_OFB, plaintext[:DES.block_size])
msgback = decCipher.decrypt(plaintext[DES.block_size:])


with open("DES-OFB-decrypt.bmp","ab") as f3:
    f3.write(b)
    f3.write(msgback)
    f3.close()
