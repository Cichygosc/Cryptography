#ifndef LCG_H_
#define LCG_H_

#include <cstddef>

using std::size_t;

class LCG
{
private:
	size_t modulus;
	size_t a;
	size_t c;
	size_t seed;
public:
	LCG(size_t modulus, size_t a, size_t c);
	size_t generateNext();
};

#endif