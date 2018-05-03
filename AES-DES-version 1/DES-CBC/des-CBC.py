import pyDes

from PIL import Image
with open("twitter.bmp", "rb") as imageFile:
  f = imageFile.read(138)
  b = bytearray(f)
  a = imageFile.read(1442910) #a = imageFile.read(363049472) para la del pinguino
imageFile.close()

data=a
k = pyDes.des(b"Asegurar", pyDes.CBC, "\0\0\0\0\0\0\0\0", pad=None, padmode=pyDes.PAD_PKCS5)
d = k.encrypt(data)

with open("DES-CBC-encrypt.bmp","ab") as f2:
    f2.write(b)
    f2.write(d)
f2.close()

c=k.decrypt(d)
with open("DES-CBC-decrypt.bmp","ab") as f3:
    f3.write(b)
    f3.write(c)
f3.close()

























#for i in range(137,len(b)):

'''
for i in range(0,3):
    print(format((b[i]),"x"))
print(type(b[0]))
print(type(format(b[i],"x")))
'''

#tmp=open("temporal.txt","w")
#tmp.write()


'''
data = b"Diamante"
k = pyDes.des(b"Asegurar", pyDes.CBC, "\0\0\0\0\0\0\0\0", pad=None, padmode=pyDes.PAD_PKCS5)
d = k.encrypt(data)
print("Encrypted: %r" % d)
print("Decrypted: %r" % k.decrypt(d))
assert k.decrypt(d) == data
'''

'''
from PIL import Image
with open("penguinlogo.bmp", "rb") as f:
    byte = f.read(1)
    while byte != b"":
        byte = f.read(1)
        print(byte)
'''

