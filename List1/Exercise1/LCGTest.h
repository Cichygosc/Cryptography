#ifndef LCGTEST_H_
#define LCGTEST_H_

#include <vector>
#include <cstddef>

using std::size_t;
using std::vector;

class LCGTest
{
private:
	size_t a;
	size_t c;
	size_t m;
	vector<size_t> lcgValues;
	vector<size_t> determinants;
	size_t calculateDet(size_t v1, size_t v2, size_t v3, size_t v4);
	size_t GCD(size_t v1, size_t v2);
	void calculateModulus();
	void calculateConstants(size_t v1, size_t v2, size_t v3);
	size_t factor(size_t value);
public:
	LCGTest();
	void addValue(size_t value);
	bool canPredict();
	size_t getNext();
	void details();
};

#endif