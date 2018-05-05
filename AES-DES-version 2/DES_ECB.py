from Crypto.Cipher import DES
from PIL import Image

def encrypt():
    with open("static/twitter.bmp", "rb") as imageFile:
        f = imageFile.read(138)
        b = bytearray(f)
        a = imageFile.read(1442910) #a = imageFile.read(363049472) para la del pinguino
        imageFile.close()

    key = b'Asegurar'
    cipher =  DES.new(key, DES.MODE_ECB)
    plaintext = a
    msg = cipher.encrypt(plaintext)


    with open("static/encrypt.bmp","ab") as f2:
        f2.write(b)
        f2.write(msg)
        f2.close()

def decrypt():
    with open("static/encrypt.bmp", "rb") as imageFile:
        f = imageFile.read(138)
        b = bytearray(f)
        a = imageFile.read(1442910) #a = imageFile.read(363049472) para la del pinguino
        imageFile.close()

    key = b'Asegurar'
    cipher =  DES.new(key, DES.MODE_ECB)
    msg = cipher.decrypt(a)

    with open("static/decrypt.bmp","ab") as f3:
        f3.write(b)
        f3.write(msg)
        f3.close()


'''
import pyDes
from PIL import Image

def encrypt():
    with open("static/twitter.bmp", "rb") as imageFile:
        f = imageFile.read(138)
        b = bytearray(f)
        a = imageFile.read(1441910)#a = imageFile.read(363049472)para la del pinguino
        imageFile.close()

    data=a
    k = pyDes.des(b"Asegurar", pyDes.ECB, "\0\0\0\0\0\0\0\0", pad=None, padmode=pyDes.PAD_PKCS5)
    d = k.encrypt(data)

    with open("static/encrypt.bmp","ab") as f2:
        f2.write(b)
        f2.write(d)
        f2.close()

def decrypt():
    with open("static/encrypt.bmp", "rb") as imageFile:
        f = imageFile.read(138)
        b = bytearray(f)
        a = imageFile.read(1441910)#a = imageFile.read(363049472)para la del pinguino
        imageFile.close()

    k = pyDes.des(b"Asegurar", pyDes.ECB, "\0\0\0\0\0\0\0\0", pad=None, padmode=pyDes.PAD_PKCS5)
    c=k.decrypt(a)
        
    with open("static/decrypt.bmp","ab") as f3:
        f3.write(b)
        f3.write(c)
        f3.close()
'''



