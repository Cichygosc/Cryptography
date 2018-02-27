#include <iostream>
#include <cstdlib>
#include <iostream>
#include <cstddef>

#include "glibcTest.h"

using namespace std;

int main()
{
	srand(time(0));
	glibcTest test;
	for (size_t i = 0; i < 32; ++i)
	{
		int randomValue = rand();
		test.addValue(randomValue);
		cout << "Current value: " << randomValue << endl;
		cout << "Can't predict yet.\n";	
	}

	for (size_t i = 0; i < 1000; ++i)
	{
		int randomValue = rand();
		test.addValue(randomValue);
		cout << "Current value: " << randomValue << endl;
		cout << "Predictable next value: " << test.getNext() << endl;
		cin.ignore();
	}

	return 0;
}