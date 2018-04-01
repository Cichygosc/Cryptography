import os, random, struct
from Crypto.Cipher import AES
from Crypto import Random
from base64 import b64encode
from base64 import b64decode
import numpy as np
import jks
import configparser

BLOCK_SIZE = 16
pad = lambda s: s + (BLOCK_SIZE - len(s) % BLOCK_SIZE) * \
				chr(BLOCK_SIZE - len(s) % BLOCK_SIZE)

unpad = lambda s: s[:-ord(s[len(s) - 1])]

def encrypt_file(key, mode, in_filename, out_filename=None, chunksize = 64 * 1024):
	if not out_filename:
		out_filename = in_filename + '.enc'

	iv = Random.new().read(AES.block_size);

	encryptor = AES.new(key, mode, iv)
	filesize = os.path.getsize(in_filename)

	with open(in_filename, 'rb') as infile:
		with open(out_filename, 'wb') as outfile:
			outfile.write(struct.pack('<Q', filesize))
			outfile.write(iv)

			while True:
				chunk = infile.read(chunksize)
				if len(chunk) == 0:
					break
				elif len(chunk) % 16 != 0:
					chunk += (' ' * (16 - len(chunk) % 16)).encode('ascii')

				outfile.write(encryptor.encrypt(chunk))


def decrypt_file(key, mode, in_filename, out_filename=None, chunksize=24*1024):
	if not out_filename:
		out_filename = os.path.splitext(in_filename)[0]

	with open(in_filename, 'rb') as infile:
		origsize = struct.unpack('<Q', infile.read(struct.calcsize('Q')))[0]
		iv = infile.read(16)
		decryptor = AES.new(key, mode, iv)

		with open(out_filename, 'wb') as outfile:
			while True:
				chunk = infile.read(chunksize)
				if len(chunk) == 0:
					break
				outfile.write(decryptor.decrypt(chunk))

			outfile.truncate(origsize)


def getKey(jks_file, passphrase, key_alias):
	keystore = jks.KeyStore.load(jks_file, passphrase)
	sk  = keystore.secret_keys[key_alias]
	return sk.key

def encryptionOracleMode(key, mode):
	iv = Random.new().read(AES.block_size)
	encryptor = AES.new(key, mode, iv)
	while(1):
		m = input("Enter text to encrypt: ")
		m = pad(m)
		print(b64encode(encryptor.encrypt(m.encode("ascii"))))

def challengeMode(key, mode):
	iv = Random.new().read(AES.block_size)
	encryptor = AES.new(key, mode, iv)
	m1 = input("Enter m1: ")
	m2 = input("Enter m2: ")
	bit = np.random.randint(0, 2)
	if bit == 0:
		c = b64encode(encryptor.encrypt(pad(m1).encode("ascii")))
	elif bit == 1:
		c= b64encode(encryptor.encrypt(pad(m2).encode("ascii")))
	print(c)


def parseType(type):
	return {
		'CBC': AES.MODE_CBC,
		'CTR': AES.MODE_CTR, 
		'OFB': AES.MODE_OFB
	}.get(type, AES.MODE_CBC)

config = configparser.ConfigParser()
config.read('config.ini')

keyStorePath = config['KeyStore']['Path']
keyAlias = config['KeyStore']['KeyAlias']
keyPassword = config['KeyStore']['Password']
encryptionModeType = config['Encryption']['Mode']
encryptionMode = parseType(encryptionModeType)

key = getKey(keyStorePath, keyPassword, keyAlias)

#encrypt_file(key, encryptionMode, 'test', 'test.enc')
#decrypt_file(key, encryptionMode, 'test.enc', 'test.dec')

programMode = config['ProgramMode']['Mode']

if programMode == 'Oracle':
	encryptionOracleMode(key, encryptionMode)
elif programMode == 'Challenge':
	challengeMode(key, encryptionMode)
else:
	print("Unsupported mode")
