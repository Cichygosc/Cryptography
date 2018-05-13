import pyasn1.codec.der.encoder
import pyasn1.type.univ
import base64

def egcd(a, b):
	x = 0
	y = 1
	u = 1
	v = 0
	while a != 0:
		q = b // a
		r = b % a
		m = x - u * q
		n = y - v * q
		b = a
		a = r
		x = u
		y = v
		u = m
		v = n
	gcd = b
	return gcd, x, y

def modinv(a, m):
	gcd, x, y = egcd(a, m)
	if gcd != 1:
		return None
	else:
		return x % m

def pempriv(n, e, d, p, q, dP, dQ, qInv):
	template = '-----BEGIN RSA PRIVATE KEY-----\n{}-----END RSA PRIVATE KEY-----\n'
	seq = pyasn1.type.univ.Sequence()
	for x in [0, n, e, d, p, q, dP, dQ, qInv]:
		seq.setComponentByPosition(len(seq), pyasn1.type.univ.Integer(x))
	der = pyasn1.codec.der.encoder.encode(seq)
	return template.format(base64.encodestring(der).decode('ascii'))

p = 1524938362073628791222322453937223798227099080053904149
q = 1385409854850246784644682622624349784560468558795524903
e = 0x010001
output_file = "key.pem"

n = p * q
phi = (p - 1)*(q - 1)
d = modinv(e, phi)
dp = modinv(e, p - 1)
dq = modinv(e, q - 1)
qi = modinv(q, p)

key = pempriv(n, e, d, p, q, dp, dq, qi)

f = open(output_file, "w")
f.write(key)
f.close()