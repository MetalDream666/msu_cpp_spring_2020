#include <cstdlib>
#include <limits>
#include <stdexcept>
#include <cstring>

#ifndef VECTOR_H
#define VECTOR_H

template <class T>
struct MyAllocator
{
	typedef T value_type;

	MyAllocator() = default;
	template <class U> constexpr MyAllocator (const MyAllocator <U>&) noexcept {}

	T* allocate(std::size_t n)
	{
		if (n > std::numeric_limits<std::size_t>::max() / sizeof(T))
		  throw std::bad_alloc();

		if (auto p = static_cast<T*>(std::malloc(n*sizeof(T))))
		  return p;

		throw std::bad_alloc();
	}
	void deallocate(T* p, std::size_t) noexcept 
	{
	  std::free(p); 
	}
};
 
template <class T, class U>
bool operator==(const MyAllocator <T>&, const MyAllocator <U>&) 
{
	return true;	
}
template <class T, class U>
bool operator!=(const MyAllocator <T>&, const MyAllocator <U>&) 
{
	return false;
}


template <class Iter>
class OddIterator: public std::iterator<std::random_access_iterator_tag, Iter>
{
private:
	Iter* current_;
	Iter* end_;

public:
	OddIterator(Iter* begin, Iter* end): current_(std::move(begin)), end_(std::move(end)) {}

	bool operator==(const OddIterator& other) const
	{
		return current_ == other.current_;
	}

	bool operator!=(const OddIterator& other) const
	{
		return !(*this == other);
	}

	OddIterator<Iter>& operator++()
	{
		if (current_ != end_)
		{
			current_++;
		}
		return *this;
	}

	Iter& operator*() const
	{
		return *current_;
	}
};


template <class T>
struct MyVector
{
private:
	MyAllocator<T> allocator;
	T* memory;
	size_t vsize;
	size_t memsize;

public:
	MyVector()
	{
		memory = allocator.allocate(5);
		memsize = 5;
		vsize = 0;
	}
	
	const T operator[](size_t n) const
	{
		if(n >= vsize)
		{
			throw std::out_of_range("OUT OF RANGE");
		}
		return memory[n];
	}
	
	T& operator[](size_t n)
	{
		if(n >= vsize)
		{
			throw std::out_of_range("OUT OF RANGE");
		}
		return memory[n];
	}
	
	size_t size()
	{
		return vsize;
	}
	
	OddIterator<T> begin()
	{
		return OddIterator<T>(memory, memory + vsize);
	}
	
	OddIterator<T> end()
	{
		return OddIterator<T>(memory + vsize, memory + vsize);
	}
	
	OddIterator<T> rbegin()
	{
		return OddIterator<T>(memory + vsize, memory);
	}
	
	OddIterator<T> rend()
	{
		return OddIterator<T>(memory - 1, memory - 1);
	}
	
	void reserve(size_t new_mem_size)
	{
		if(new_mem_size <= memsize)
			return;
			
		T* new_memory = allocator.allocate(new_mem_size);
		std::memcpy(new_memory, memory, vsize*sizeof(T));
		allocator.deallocate(memory, memsize);
		memory = new_memory;
		memsize = new_mem_size;
	}
	
	void resize(size_t new_size, T value = T())
	{
		if(new_size > vsize)
		{
			(*this).reserve(new_size);
			OddIterator<T> it = OddIterator<T>(memory + vsize, memory + new_size); 
			vsize = new_size;
			for(;it != (*this).end(); ++it)
			{
				(*it) = value;
			}
		}
		vsize = new_size;
	}
	
	void push_back(const T& a)
	{
		if(vsize >= memsize)
		{
			(*this).reserve(vsize*2);			
		}
		memory[vsize] = a;
		vsize++;
	}
	
	T pop_back()
	{
		if(vsize == 0)
		{
			throw std::out_of_range("VECTOR IS EMPTY");
		}
		return memory[--vsize];
	}
	
	void clear()
	{
		vsize = 0;
	}
	
	bool empty()
	{
		return (vsize == 0);
	}
	
	~MyVector()
	{
		allocator.deallocate(memory, memsize);
	}
};

#endif

