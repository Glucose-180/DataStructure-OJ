#include <string>
#include <vector>
#include <iostream>

using namespace std;

int main()
{
	string s, t, r;
	int i;
	char c;
	vector<int> loc;

	cin >> s >> t;
	for (i = 0; i < s.size(); ++i)
	{
		c = s[i];
		if (r.find(c) == string::npos && t.find(c) == string::npos)
		{
			r += c;
			loc.push_back(i);
		}
	}
	if (r.size() == 0)
	{
		cout << "-1";
		return 0;
	}
	cout << r << ' ';
	for (i = 0; i < loc.size(); ++i)
		cout << loc.at(i);
	return 0;
}
