#include <iostream>
#include <string>
#include <algorithm>

#define L 100

//char* str[L];
char* p;

void strrev_g(char* s);

using namespace std;

int main()
{
	string str;
	getline(cin, str);
	reverse(str.begin(), str.end());
	cout << str;
	return 0;
}

void strrev_g(char* s)
{
	char c = *s;
	if (c == '\0')
		return;
	strrev_g(s + 1);
	*p++ = c;
}