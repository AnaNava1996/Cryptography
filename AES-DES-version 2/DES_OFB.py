from Crypto.Cipher import DES
from PIL import Image
from Crypto import Random
def encrypt():
    with open("static/twitter.bmp", "rb") as imageFile:
      f = imageFile.read(138)
      b = bytearray(f)
      a = imageFile.read() #a = imageFile.read(363049472) para la del pinguino
    imageFile.close()

    key = b'Eight888'
    iv = Random.new().read(DES.block_size)
    cipher = DES.new(key, DES.MODE_OFB, iv)
    msg = iv + cipher.encrypt(a)

    with open("static/encrypt.bmp","ab") as f3:
        f3.write(b)
        f3.write(msg)
        f3.close()

def decrypt():
    with open("static/encrypt.bmp", "rb") as imageFile:
      f = imageFile.read(138)
      b = bytearray(f)
      a = imageFile.read() #a = imageFile.read(363049472) para la del pinguino
    imageFile.close()

    key = b'Eight888'
    decCipher = DES.new(key, DES.MODE_OFB, a[:DES.block_size])
    msgback = decCipher.decrypt(a[DES.block_size:])

    with open("static/decrypt.bmp","ab") as f3:
        f3.write(b)
        f3.write(msgback)
        f3.close()
