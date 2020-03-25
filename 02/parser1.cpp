#include <iostream>
#include <cstdlib>
#include <string>
#include <functional>
#include <vector>

using namespace std;

typedef function<void ()> fStartEndType;
typedef function<void (const string&)> fStringType;
typedef function<void (int)> fNumberType;


class Parser
{
public:
	Parser(){};
	~Parser(){};
	
	int handle(string ss);
	
	void registerCallbackFunctionOnStart(fStartEndType onStart);
	void registerCallbackFunctionOnEnd(fStartEndType onEnd);
	void registerCallbackFunctionOnString(fStringType onString);
	void registerCallbackFunctionOnNumber(fNumberType onNumber);
	
private:
	fStartEndType fStartParser = nullptr;
	fStartEndType fEndParser = nullptr;
	fStringType fStringHandle = nullptr;
	fNumberType fNumberHandle = nullptr;
	
	void parse(string ss);
	
	bool isNum(string s);
	
	vector<string> sts;
	int vsize = 0;

};

int Parser::handle(string ss)
{
	
	parse(ss);
	if(fStartParser == nullptr)
	{
		cout << "StartParser function not defined" << endl;
		return 1;
	}
	if(fStartParser == nullptr)
	{
		cout << "EndParser function not defined" << endl;
		return 2;
	}
	if(fStartParser == nullptr)
	{
		cout << "StringHandle function not defined" << endl;
		return 3;
	}
	if(fStartParser == nullptr)
	{
		cout << "NumberHandle function not defined" << endl;
		return 4;
	}
	
	fStartParser();
	
	for(int i = 0; i < vsize; i++)
	{
		if(isNum(sts[i]))
		{
			fNumberHandle(stoi(sts[i]));
		}
		else
		{
			fStringHandle(sts[i]);
		}
	}
	fEndParser();
	return 0;
}

bool Parser::isNum(string s)
{
	return (isdigit(s[0]));
}

void Parser::registerCallbackFunctionOnStart(fStartEndType onStart)
{
	fStartParser = onStart;
}

void Parser::registerCallbackFunctionOnEnd(fStartEndType onEnd)
{
	fEndParser = onEnd;
}

void Parser::registerCallbackFunctionOnString(fStringType onString)
{
	fStringHandle = onString;
}

void Parser::registerCallbackFunctionOnNumber(fNumberType onNumber)
{
	fNumberHandle = onNumber;
}

void Parser::parse(string ss)
{
	int is = 0;
	for(int i = 0; i < (int)ss.length(); i++)
	{
		if((isspace(ss[i])) || (i == (int)ss.length()-1))
		{
			if((int)sts.size() <= vsize)
			{
				sts.resize((vsize+1)*2);
			}	
			if((i == 0) || isspace(ss[i-1]))
			{
				is++;
				continue;
			}
			else
			{
				if((i == (int)ss.length()-1) && !(isspace(ss[i])))
				{
					sts[vsize++] = ss.substr(is);
				}
				else
				{
					sts[vsize++] = ss.substr(is, i-is);
					is = i+1;
				}
			}
		}
	}
}


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
		
	string a = string("    eto   stroka 12345 haha lol	");
	int err = p.handle(a);
	return err;
}
