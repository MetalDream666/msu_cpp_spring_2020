#ifndef PARSER_H
#define PARSER_H

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

#endif
