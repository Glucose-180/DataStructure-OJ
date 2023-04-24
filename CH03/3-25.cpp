#include <iostream>

using namespace std;

int main()
{
	int n, p = 1;

	cin >> n;
	while (n > 0)
	{
		p *= n;
		n /= 2;
	}
	cout << p;
	return 0;
}