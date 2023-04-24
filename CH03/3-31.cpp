#include <iostream>
#include <string>

using namespace std;

int main()
{
	char ch;
	string str;
	int i = 0, j;

	while (cin.get(ch))
		if (ch == '@')
			break;
		else
			str += ch;
	j = str.length() - 1;
	for (; i < j; ++i, --j)
		if (str[i] != str[j])
			break;
	if (i < j)
		cout.put('0');
	else
		cout.put('1');
	return 0;
}