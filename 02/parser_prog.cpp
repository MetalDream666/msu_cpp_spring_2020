#include "parser.h"

void fStart()
{
	cout << "Start parsing" << endl;
}

void fEnd()
{
	cout << "End parsing" << endl;
}

void fString(const string& s)
{
	cout << "This is string '" << s.c_str() << "'" << endl;
}

void fNumber(int x)
{
	cout << "This is number " << x << endl;
}

int main()
{
	Parser p;
	
	p.registerCallbackFunctionOnStart(fStart);
	p.registerCallbackFunctionOnEnd(fEnd);
	p.registerCallbackFunctionOnString(fString);
	p.registerCallbackFunctionOnNumber(fNumber);
		
	string a;
	string s;
	cout << "Enter your string:" << endl;
	while(!(feof(stdin)))
	{
		getline(cin, a);
		s += a;
	}
	
	int err = p.handle(s);
	return err;
}
