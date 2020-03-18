#include "parser.h"

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
