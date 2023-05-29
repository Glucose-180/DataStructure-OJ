#include <vector>
#include <iostream>

using namespace std;

int main()
{
	int dt;
	char c;
	unsigned int i;
	vector<int> brt;
	// add
	do {
		cin >> dt;
		cin.get(c);
		brt.push_back(dt);
	} while (c == ' ');

	// search
	while (cin >> dt)
	{
		for (i = 0; i < brt.size(); ++i)
		{
			if (brt.at(i) == dt)
			{
				cout << '1' << ' ';
				break;
			}
		}
		if (i == brt.size())
			cout << '0' << ' ';
	}
	return 0;
}
