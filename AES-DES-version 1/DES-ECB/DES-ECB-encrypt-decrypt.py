import pyDes

from PIL import Image
with open("twitter.bmp", "rb") as imageFile:
  f = imageFile.read(138)
  b = bytearray(f)
  a = imageFile.read(1441910)#a = imageFile.read(363049472)para la del pinguino
imageFile.close()

data=a
k = pyDes.des(b"Asegurar", pyDes.ECB, "\0\0\0\0\0\0\0\0", pad=None, padmode=pyDes.PAD_PKCS5)
d = k.encrypt(data)

with open("DES-ECB-encrypt.bmp","ab") as f2:
    f2.write(b)
    f2.write(d)
f2.close()

c=k.decrypt(d)
with open("DES-ECB-decrypt.bmp","ab") as f3:
    f3.write(b)
    f3.write(c)
f3.close()




