#ifndef SERIALIZER_H
#define SERIALIZER_H

#include <sstream>
#include <cassert>

enum class Error
{
    NoError,
    CorruptedArchive
};


class Serializer
{
    static constexpr char Separator = ' ';
    std::ostream& out_;
    
public:
    explicit Serializer(std::ostream& out);
    
    template <class T> Error save(T& object)
	{
		return object.serialize(*this);
	}

	template <class... ArgsT> Error operator()(ArgsT&&... args)
	{
		return process(args...);
	}
	
	
    
private:
	template <class T> Error process(T&& val)
	{
		return toStream(val);
	}

	template <class T, class... Args> Error process(T&& val, Args&&... args)
	{
		Error err = toStream(val);
		if(err != Error::NoError)
		{
			return err;
		}
		out_ << Separator;
		return process(std::forward<Args>(args)...);
	}
		  
	template <class T> Error toStream(T val)
	{
		return Error::CorruptedArchive;
	}
	
    Error toStream(uint64_t a);
	Error toStream(bool t);

};

class Deserializer
{
	std::istream& in_;
	
public:
	explicit Deserializer(std::istream& in);
    
    template <class T> Error load(T& object)
	{
		return object.deserialize(*this);
	}

	template <class... ArgsT> Error operator()(ArgsT&&... args)
	{
		return process(args...);
	}

	
private:
	
	template <class T> Error process(T&& val)
	{
		return fromStream(val);
	}

	template <class T, class... Args> Error process(T&& val, Args&&... args)
	{
		Error err = fromStream(val);
		if(err != Error::NoError)
		{
			return err;
		}
		return process(std::forward<Args>(args)...);
	}
		
	template <class T> Error fromStream(T val)
	{
		return Error::CorruptedArchive;
	}

    Error fromStream(uint64_t& a);
	Error fromStream(bool& t);

};

#endif
