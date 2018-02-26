#include "LCGTest.h"

#include <cstdlib>
#include <iostream>
#include <cstddef>
#include <climits>

using std::size_t;
using std::cout;
using std::endl;

LCGTest::LCGTest()
	:a{0}, c{0}, m{0}, seed{0}, constantSeries{false}
{}

long long LCGTest::getNext()
{
	if (constantSeries)
	{
		long long lastValue = values.back();
		for (size_t i = 0; i < values.size(); ++i)
		{
			if (lastValue == values[i])
				return values[i + 1];
		}
	} 
	if (m == 0) return 0;
	if (a == -1) return 0;
	return (a * values[values.size() - 1] + c) % m;
}

void LCGTest::addValue(long long value)
{
	values.push_back(value);

	if (canPredict())
	{
		calculateModulus();
		if (!constantSeries)
		{
			calculateMultiplier();
			if (a != -1)
			{
				calculateIncrement();
				calculateSeed();
			}
		}
	}
}

bool LCGTest::canPredict()
{
	return values.size() > 3;
}

void LCGTest::calculateModulus()
{
	vector<long long> diffs;
	for(size_t i = 1; i < values.size(); ++i)
	{
		diffs.push_back(values[i] - values[i - 0]);
	}

	size_t zeroesAmount = diffs.size() - 2;
	vector<long long> zeroes;
	for (size_t i = 0; i < zeroesAmount; ++i)
	{
		zeroes.push_back(values[i + 2] * values[i] - values[i + 1] * values[i + 1]);
	}

	m = zeroes[0];
	for (size_t i = 1; i < zeroes.size(); ++i)
	{
		m = GCD(m, zeroes[i]);
	}

	m = llabs(m);

	if (m == 0)
	{
		constantSeries = true;
		return;
	}

	constantSeries = false;
}

void LCGTest::calculateMultiplier()
{
	for (size_t i = 0; i < values.size() - 2; ++i)
	{
		long long inverse = modInverse(values[i + 1] - values[i], m);
		if (inverse != -1)
		{
			a = modulo((values[i + 2] - values[i + 1]) * inverse, m);
			return;
		}
	}
	a = -1;
}

void LCGTest::calculateIncrement()
{
	c = modulo(values[1] - values[0] * a, m);
}

void LCGTest::calculateSeed()
{
	seed = modulo((values[0] - c) * modInverse(a, m), m);
}


long long LCGTest::GCD(long long a, long long b)
{
	if (b == 0) return a;
	return GCD(b, a % b);
}


long long LCGTest::gcdExtended(long long a, long long b, long long *x, long long *y)
{
    if (a == 0)
    {
        *x = 0, *y = 1;
        return b;
    }
 
    long long x1, y1; 
    long long gcd = gcdExtended(b%a, a, &x1, &y1);
 
    *x = y1 - (b/a) * x1;
    *y = x1;
 
    return gcd;
}

long long LCGTest::modInverse(long long a, long long m)
{
    long long x, y;
    long long g = gcdExtended(a, m, &x, &y);
    if (g != 1)
    {
        return -1;
    }
    else
    {
        return modulo(x, m);
    }
}

long long LCGTest::modulo(long long a, long long b)
{
	return ((a % b) + b) % b;
}

void LCGTest::details()
{
	cout << "Details: a: " << a << " c: " << c << " m: " << m << " seed: " << seed << endl;
}

