#ifndef GLIBC_TEST_H_
#define GLIBC_TEST_H_

#include <vector>
#include <iostream>

using std::vector;

class glibcTest
{
private:
	vector<int> values;

private:
	bool canPredict()
	{
		return values.size() > 30;
	}

public:
	void addValue(int value)
	{
		values.push_back(value);
	}

	const long long getNext()
	{
		if (canPredict())
		{	
			const long long o31 = values[values.size() - 31];
			const long long o3 = values[values.size() - 3];

			return (o31 + o3) % (1 << 31);
		}

		return 0;
	}
};

#endif