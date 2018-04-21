import os, random, struct
from Crypto.Cipher import AES
from Crypto import Random
from binascii import hexlify, unhexlify

KEY_LENGTH = 1
PUZZLES_AMOUNT = 2 ** (KEY_LENGTH * 8)

pad = lambda s: s + (AES.block_size - len(s) % AES.block_size) * \
				chr(AES.block_size - len(s) % AES.block_size)

unpad = lambda s: s[:-ord(s[len(s) - 1])]

def utf8len(s):
	return len(s.decode('utf-8'))

iv = Random.new().read(AES.block_size)

def encrypt(key, message):
	encryptor = AES.new(key, AES.MODE_CBC, iv)
	message = pad(message)
	return hexlify(encryptor.encrypt(message.encode("utf-8")))

def decrypt(key, cipher):
	decryptor = AES.new(key, AES.MODE_CBC, iv)
	return decryptor.decrypt(unhexlify(cipher))

def generatePuzzle(index):
	puzzle_key = hexlify(os.urandom(24))
	random_key = hexlify(os.urandom(KEY_LENGTH))
	random_key_string = random_key.decode("utf-8")
	puzzle_key_string = puzzle_key.decode("utf-8")
	if len(random_key_string) < AES.block_size:
		random_key_string += '0' * (AES.block_size - len(random_key_string))
		random_key = random_key_string.encode('utf-8')
	message = str(index) + " " + puzzle_key_string
	cipher = encrypt(random_key, message)
	return (index, puzzle_key, cipher)

def getMessage(cipher):
	for random_key in range(0, PUZZLES_AMOUNT):
		random_key_string = str(format(random_key, 'x')).zfill(KEY_LENGTH * 2)
		random_key_string += '0' * (AES.block_size - len(random_key_string))
		key = random_key_string.encode('utf-8')
		valid = True
		message = ''
		try:
			message = decrypt(key, cipher).decode('utf-8')
		except UnicodeDecodeError:
			valid = False
		if valid:
			return message

puzzles = []

for i in range(0, PUZZLES_AMOUNT):
	puzzles.append(generatePuzzle(i))

index = random.randint(0, PUZZLES_AMOUNT - 1)

cipher = puzzles[index][2]
message = getMessage(cipher).split(" ")
index = int(message[0])
key = message[1].encode('utf-8')

print("Bob:")
print(index)
print(key)

alice_key = ''
for i in range(0, PUZZLES_AMOUNT):
	if puzzles[i][0] == index:
		alice_key = puzzles[i][1]
		break

print("Alice:")
print(alice_key)






