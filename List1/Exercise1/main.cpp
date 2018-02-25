#include "LCG.h"
#include "LCGTest.h"

#include <iostream>

using namespace std;

int main()
{
	LCG lcg(10, 3, 0);
	LCGTest test;
	for (size_t i = 0; i < 10; ++i)
	{
		size_t nextValue = lcg.generateNext();
		test.addValue(nextValue);
		cout << "Current value: " << nextValue << endl;
		cout << "Predictable next value: " << test.getNext() << endl;
		test.details();
		cin.ignore();
	}
	return 0;
}