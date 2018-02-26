#include "LCG.h"
#include "LCGTest.h"

#include <iostream>

using namespace std;

int main()
{
	LCG lcg(2147483647, 16807, 0);
	LCGTest test;
	for (size_t i = 0; i < 10; ++i)
	{
		long long nextValue = lcg.generateNext();
		test.addValue(nextValue);
		cout << "Current value: " << nextValue << endl;
		cout << "Predictable next value: " << test.getNext() << endl;
		test.details();
		cout << endl;
	}
	return 0;
}