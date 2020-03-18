#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <cstdlib>
#include <string>
#include <functional>
#include <vector>

typedef std::function<void ()> fStartEndType;
typedef std::function<void (const std::string&)> fStringType;
typedef std::function<void (int)> fNumberType;

class Parser
{
public:
	Parser(){};
	~Parser(){};
	
	
	void parse(const std::string& ss);
	
	void registerCallbackFunctionOnStart(fStartEndType onStart);
	void registerCallbackFunctionOnEnd(fStartEndType onEnd);
	void registerCallbackFunctionOnString(fStringType onString);
	void registerCallbackFunctionOnNumber(fNumberType onNumber);
	
private:
	fStartEndType fStartParser = nullptr;
	fStartEndType fEndParser = nullptr;
	fStringType fStringHandle = nullptr;
	fNumberType fNumberHandle = nullptr;
	
	
	
	bool isNum(char c);
	
	void handle(std::string ss);
};

#endif
