#ifndef LCG_H_
#define LCG_H_

class LCG
{
private:
	long long modulus;
	long long a;
	long long c;
	long long seed;
public:
	LCG(long long modulus, long long a, long long c);
	long long generateNext();
};

#endif