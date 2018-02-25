#include "LCG.h"

#include <cstdio>
#include <cstdlib>
#include <ctime>

LCG::LCG(size_t modulus, size_t a, size_t c)
	:modulus{modulus}, a{a}, c{c}
{
	srand(time(NULL));
	seed = rand() % modulus;
}

size_t LCG::generateNext()
{
	seed = (a * seed + c) % modulus;
	return seed;
}