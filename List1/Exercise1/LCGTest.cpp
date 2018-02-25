#include "LCGTest.h"

#include <cstdlib>
#include <iostream>

using std::cout;
using std::endl;

LCGTest::LCGTest()
	:a{0}, c{0}, m{0}
{}

void LCGTest::addValue(size_t value)
{
	lcgValues.push_back(value);
	if (canPredict())
	{
		calculateModulus();
		calculateConstants(lcgValues[0], lcgValues[1], lcgValues[2]);
	}
}

bool LCGTest::canPredict()
{
	return lcgValues.size() > 3;
}

void LCGTest::calculateModulus()
{
	determinants.clear();
	size_t determinantsLength = lcgValues.size() - 3;
	for (size_t i = 0; i < determinantsLength; i ++)
	{
		determinants.push_back(calculateDet(lcgValues[i], lcgValues[i + 1], lcgValues[i + 2], lcgValues[i + 3]));
		cout << "Calculated determinant " << determinants.back() << endl;
	}

	m = determinants[0];
	for (size_t i = 1; i < determinants.size(); ++i)
	{
		m = GCD(m, determinants[i]);
	}

	m = factor(m);
}

size_t LCGTest::factor(size_t value)
{
	const unsigned int sprimes[16] = {0x02, 0x03, 0x05, 0x07, 0x0B, 0x0D, 0x11, 0x13, 
									  0x17, 0x1D, 0x1F, 0x25, 0x29, 0x2B, 0x2F, 0x35};

	size_t counter = 0;
	while (counter < 16)
	{
		if (value % sprimes[counter] == 0)
			value /= sprimes[counter];
		else 
			counter++;
	}

	return value;
}

void LCGTest::calculateConstants(size_t v1, size_t v2, size_t v3)
{
	a = ((v2 - v3) / (v1 - v2)) % m;
	c = (v2 - (a * v1 % m)) % m;
}


size_t LCGTest::calculateDet(size_t v1, size_t v2, size_t v3, size_t v4)
{
	return abs(v1 * v3 + v2 * v4 + v2 * v3 - v3 * v3 - v1 * v4 - v2 * v2);
}

size_t LCGTest::GCD(size_t v1, size_t v2)
{
	if (v2 == 0) return v1;
	return GCD(v2, v1 % v2);
}

size_t LCGTest::getNext()
{
	if (m == 0) return 0;
	return (a * lcgValues[lcgValues.size() - 1] + c) % m;
}

void LCGTest::details()
{
	cout << "Details: a: " << a << " c: " << c << " m: " << m << endl;
}