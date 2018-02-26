#include "LCG.h"

#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <iostream>


LCG::LCG(long long modulus, long long a, long long c)
	:modulus{modulus}, a{a}, c{c}
{
	srand(time(NULL));
	seed = rand() % (modulus - 1) + 1;
	std::cout << "seed: " << seed << std::endl;
}

long long LCG::generateNext()
{
	seed = (a * seed + c) % modulus;
	return seed;
}