from flask import Flask, render_template, request
from time import sleep
import os

app = Flask(__name__)

import AES_CBC as acbc
import AES_CFB as acfb
import AES_ECB as aecb
import AES_OFB as aofb

import DES_CBC as dcbc
import DES_CFB as dcfb
import DES_ECB as decb
import DES_OFB as dofb

@app.route('/')
def hello_world():
    return render_template('index.html')

@app.route('/cripto', methods=['GET', 'POST'])
def cripto():
    if request.method == 'POST':
        try:
            os.remove("static/encrypt.bmp")
            os.remove("static/decrypt.bmp")
        except OSError:
            pass
        if request.form['cif']=="DES-CBC":dcbc.encrypt()
        elif request.form['cif']=="DES-CFB":dcfb.encrypt()
        elif request.form['cif']=="DES-ECB":decb.encrypt()
        elif request.form['cif']=="DES-OFB":dofb.encrypt()
        elif request.form['cif']=="AES-CBC":acbc.encrypt()
        elif request.form['cif']=="AES-CFB":acfb.encrypt()
        elif request.form['cif']=="AES-ECB":aecb.encrypt()
        elif request.form['cif']=="AES-OFB":aofb.encrypt()

        #sleep(5)
        
        if request.form['des']=="DES-CBC":dcbc.decrypt()
        elif request.form['des']=="DES-CFB":dcfb.decrypt()
        elif request.form['des']=="DES-ECB":decb.decrypt()
        elif request.form['des']=="DES-OFB":dofb.decrypt()
        elif request.form['des']=="AES-CBC":acbc.decrypt()
        elif request.form['des']=="AES-CFB":acfb.decrypt()
        elif request.form['des']=="AES-ECB":aecb.decrypt()
        elif request.form['des']=="AES-OFB":aofb.decrypt()

        return "success"
        
    else: return "0"

app.run(debug = True)
