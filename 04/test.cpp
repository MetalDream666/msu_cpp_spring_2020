#include <iostream>

#include "serializer.h"

using namespace std;

struct Data
{
    uint64_t a;
    bool b;
    uint64_t c;
    
    template <class Serializer> Error serialize(Serializer& serializer)
    {
		return serializer(a, b, c);
	}
    
    template <class Deserializer> Error deserialize(Deserializer& deserializer)
    {
		return deserializer(a, b, c);
	}
};

int main()
{
	std::stringstream stream;
	Data x { 1, true, 2 };

	Serializer serializer(stream);
	serializer.save(x);
	
	cout << stream.str() << endl;

	Data y { 0, false, 0 };

	Deserializer deserializer(stream);
	const Error err = deserializer.load(y);

	assert(err == Error::NoError);

	assert(x.a == y.a);
	assert(x.b == y.b);
	assert(x.c == y.c);

	return 0;
}
