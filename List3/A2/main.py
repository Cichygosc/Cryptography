import os, random, struct, sys
from Crypto.Cipher import AES
from Crypto import Random
import jks
import configparser
import numpy as np

BLOCK_SIZE = 16
pad = lambda s: s + (BLOCK_SIZE - len(s) % BLOCK_SIZE) * \
				chr(BLOCK_SIZE - len(s) % BLOCK_SIZE)

unpad = lambda s: s[:-ord(s[len(s) - 1])]

def getKey(jks_file, passphrase, key_alias):
	keystore = jks.KeyStore.load(jks_file, passphrase)
	sk = keystore.secret_keys[key_alias]
	return sk.key

def challenge(key, iv, m1, m2):
	bit = np.random.randint(0, 2)
	if bit == 0:
		(iv, c) = encrypt(key, iv, m1)
	elif bit == 1:
		(iv, c) = encrypt(key, iv, m2)
	return (iv, c, bit)

def encrypt(key, iv, m):
	encryptor = AES.new(key, AES.MODE_CBC, iv)
	if len(m) % 16 != 0:
		m += (' ' * (16 - len(m) % 16)).encode('ascii')
	return (iv, encryptor.encrypt(m))

def incIV(iv):
	int_iv = int.from_bytes(iv, sys.byteorder)
	int_iv += 1
	return int_iv.to_bytes(16, sys.byteorder)

config = configparser.ConfigParser()
config.read('config.ini')

keyStorePath = config['KeyStore']['Path']
keyAlias = config['KeyStore']['KeyAlias']
keyPassword = config['KeyStore']['Password']

key = getKey(keyStorePath, keyPassword, keyAlias)

iv = Random.new().read(AES.block_size)

m1 = b'Hello'
m2 = b'World'

(used_iv, c, bit) = challenge(key, iv, m1, m2)

predicted_next_iv = incIV(used_iv)
mc = int.from_bytes(b'Hello', sys.byteorder) ^ int.from_bytes(used_iv, sys.byteorder) ^ int.from_bytes(predicted_next_iv, sys.byteorder)
mc_enc = mc.to_bytes(len(m1), sys.byteorder)

iv = incIV(iv)
(ivc, cc) = encrypt(key, iv, mc_enc)
if cc == c:
	print("Message %s was encrypted" % m1)
else:
	print("Message %s was encrypted" % m2)

print(bit)