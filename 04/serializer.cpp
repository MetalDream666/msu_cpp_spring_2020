#include <iostream>

#include "serializer.h"

/*Serializer::Serializer(std::ostream& out):out_(out) {}

template <class T> Error Serializer::save(T& object)
{
    return object.serialize(*this);
}

template <class... ArgsT> Error Serializer::operator()(ArgsT&&... args)
{
    return process(args...);
}*/


template <class T> Error Serializer::process(T&& val)
{
	return toStream(val);
}

template <class T, class... Args> Error Serializer::process(T&& val, Args&&... args)
{
	Error err = toStream(val);
	if(err != Error::NoError)
	{
		return err;
	}
	out_ << Separator;
	return process(std::forward<Args>(args)...);
}
      
template <class T> Error Serializer::toStream(T val)
{
	return Error::CorruptedArchive;
}
    
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

/*template <class T> Error Deserializer::load(T& object)
{
    return object.deserialize(*this);
}

template <class... ArgsT> Error Deserializer::operator()(ArgsT&&... args)
{
    return process(args...);
}*/
	

template <class T> Error Deserializer::process(T&& val)
{
	return fromStream(val);
}

template <class T, class... Args> Error Deserializer::process(T&& val, Args&&... args)
{
	Error err = fromStream(val);
	if(err != Error::NoError)
	{
		return err;
	}
	return process(std::forward<Args>(args)...);
}
	
template <class T> Error Deserializer::fromStream(T val)
{
	return Error::CorruptedArchive;
}
    
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
