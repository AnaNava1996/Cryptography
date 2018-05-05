from Crypto.Cipher import AES
from PIL import Image
from Crypto import Random
def encrypt():
    with open("static/twitter.bmp", "rb") as imageFile:
      f = imageFile.read(138)
      b = bytearray(f)
      a = imageFile.read(1442910) #a = imageFile.read(363049472) para la del pinguino
    imageFile.close()

    key = b'AsegurarAsegurarAsegurarAsegurar'
    iv = Random.new().read(AES.block_size)
    cipher = AES.new(key, AES.MODE_OFB, iv)
    msg = iv + cipher.encrypt(a)

    with open("static/encrypt.bmp","ab") as f3:
        f3.write(b)
        f3.write(msg)
        f3.close()

def decrypt():
    with open("static/encrypt.bmp", "rb") as imageFile:
      f = imageFile.read(138)
      b = bytearray(f)
      a = imageFile.read(1442910) #a = imageFile.read(363049472) para la del pinguino
    imageFile.close()

    key = b'AsegurarAsegurarAsegurarAsegurar'
    decCipher = AES.new(key, AES.MODE_OFB, a[:AES.block_size])
    msgback = decCipher.decrypt(a[AES.block_size:])


    with open("static/decrypt.bmp","ab") as f3:
        f3.write(b)
        f3.write(msgback)
        f3.close()


'''

from Crypto.Cipher import AES
from PIL import Image

def encrypt():
    from Crypto.Cipher import AES
    from PIL import Image
    with open("static/twitter.bmp", "rb") as imageFile:
        f = imageFile.read(138)
        b = bytearray(f)
        a = imageFile.read(1442910) #a = imageFile.read(363049472) para la del pinguino
        imageFile.close()

    key = b'AsegurarAsegurarAsegurarAsegurar'
    cipher =  AES.new(key, AES.MODE_CBC)
    ciphering = AES.new(key, AES.MODE_CBC)
    plaintext = a
    msg = cipher.iv + cipher.encrypt(plaintext)
    msg2 = ciphering.iv + ciphering.encrypt(msg)

    with open("static/encrypt.bmp","ab") as f2:
        f2.write(b)
        f2.write(msg2)
        f2.close()

def decrypt():
    from Crypto.Cipher import AES
    from PIL import Image
    with open("static/encrypt.bmp", "rb") as imageFile:
        f = imageFile.read(138)
        b = bytearray(f)
        a = imageFile.read(1442910) #a = imageFile.read(363049472) para la del pinguino
        imageFile.close()

    key = b'AsegurarAsegurarAsegurarAsegurar'
    cipher =  AES.new(key, AES.MODE_CBC)
    ciphering = AES.new(key, AES.MODE_CBC)
    msg2 = ciphering.decrypt(a)
    msg = cipher.decrypt(msg2)

    with open("static/decrypt.bmp","ab") as f3:
        f3.write(b)
        f3.write(msg)
        f3.close()
'''
