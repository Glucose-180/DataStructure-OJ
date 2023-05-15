#include <iostream>
#include <vector>

using namespace std;

int main()
{
	int low, high, unit;
	int status;
	int n, i;
	int start, size;
	bool in = false;
	bool ex = false;

	cin >> low >> high >> unit;
	n = (high - low) / unit;
	for (i = 0; i < n; ++i)
	{
		cin >> status;
		if (status == 0)
		{
			ex = true;
			if (in == false)
			{
				in = true;
				start = low + i * unit;
				size = unit;
			}
			else
			{
				size += unit;
			}
		}
		else
		{
			if (in)
				cout << '0' << ' ' << start << ' ' << size << endl;
			in = false;
		}
	}
	if (in)
	{
		cout << '0' << ' ' << start << ' ' << size << endl;
	}
	else if (!ex)
		cout << "0 0 0" << endl;
	return 0;
}