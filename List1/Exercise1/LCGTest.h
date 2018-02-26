#ifndef LCGTEST_H_
#define LCGTEST_H_

#include <vector>

using std::vector;

class LCGTest
{
private:
	long long a;
	long long c;
	long long m;
	long long seed;
	vector<long long> values;
	bool constantSeries;

private:
	bool canPredict();
	void calculateModulus();
	void calculateMultiplier();
	void calculateIncrement();
	void calculateSeed();

	long long GCD(long long a, long long b);
	long long gcdExtended(long long a, long long b, long long *x, long long *y);
	long long modInverse(long long a, long long m);
	long long modulo(long long a, long long b);

public:
	LCGTest();
	void addValue(long long value);
	long long getNext();
	void details();
};

#endif