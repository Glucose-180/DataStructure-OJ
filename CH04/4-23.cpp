#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

int main()
{
	string str, strinv;

	getline(cin, str);
	getline(cin, str);
	strinv = str;
	reverse(strinv.begin(), strinv.end());
	if (strinv == str)
		cout << '1';
	else
		cout << '0';
	return 0;
}
