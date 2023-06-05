#include <iostream>

const unsigned int L = 100U;

using namespace std;

typedef int data_t;

data_t dt[L];
unsigned int ymr[L];

int main()
{
	unsigned int i, j, n;

	for (i = 0U; i < L; ++i)
		if (!(cin >> dt[i]))
			break;
	n = i;

	for (i = 0U; i < n; ++i)
	{
		unsigned int ymr_t = 0U;
		for (j = 0U; j < n; ++j)
		{
			if (dt[j] < dt[i])
				++ymr_t;
		}
		ymr[i] = ymr_t;
	}

	for (i = 0U; i < n; ++i)
		cout << ymr[i] << ' ';
	return 0;
}
