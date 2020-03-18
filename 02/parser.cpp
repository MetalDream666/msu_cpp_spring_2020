#include "parser.h"

void Parser::handle(std::string ss)
{
	if(isNum(ss[0]) && (fNumberHandle != nullptr))
	{
		fNumberHandle(stoi(ss));
	}
	else if (fStringHandle != nullptr)
	{
		fStringHandle(ss);
	}
}

void Parser::parse(const std::string& ss)
{
	if(fStartParser != nullptr)
	{
		fStartParser();
	}
	int is = 0;
	for(size_t i = 0; i < ss.length(); i++)
	{
		if((isspace(ss[i])) || (i == ss.length()-1))
		{
			if((i == 0) || isspace(ss[i-1]))
			{
				is++;
				continue;
			}
			else
			{
				if((i == ss.length()-1) && !(isspace(ss[i])))
				{
					handle(ss.substr(is));
				}
				else
				{
					handle(ss.substr(is, i-is));
					is = i+1;
				}
			}
		}
	}
	if(fEndParser != nullptr)
	{
		fEndParser();
	}
}

bool Parser::isNum(char c)
{
	return (isdigit(c));
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
