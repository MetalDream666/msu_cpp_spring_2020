#include <iostream>

#include "serializer.h"

Serializer::Serializer(std::ostream& out):out_(out) {}


    
Error Serializer::toStream(uint64_t a)
{
	out_ << a;
	return Error::NoError;
}
	
Error Serializer::toStream(bool t)
{
	if(t)
	{
		out_ << "true";
	}
	else
	{
		out_ << "false";
	}
	return Error::NoError;
}



Deserializer::Deserializer(std::istream& in):in_(in) {}
    
Error Deserializer::fromStream(uint64_t& a)
{
	std::string text;
	in_ >> text;

	uint64_t aa;
	try
	{
		aa = std::stoull(text);
	}
	catch(std::logic_error& ex)
	{
		return Error::CorruptedArchive;
	}

	a = aa;
	return Error::NoError;
}
	
Error Deserializer::fromStream(bool& t)
{
	std::string text;
	in_ >> text;

	if (text == "true")
		t = true;
	else if (text == "false")
		t = false;
	else
		return Error::CorruptedArchive;

	return Error::NoError;
}
