#ifndef SJTU_VECTOR_HPP
#define SJTU_VECTOR_HPP

#include "exceptions.hpp"

#include <climits>
#include <cstddef>
#include <cstring>

namespace sjtu 
{
/**
 * a data container like std::vector
 * store data in a successive memory and support random access.
 * 
 * assume T(&T) and ~T() exist
 */
template<typename T>
class vector
{
public:
	class const_iterator;
	/// iterator with mutable contents
	class iterator 
	{
	public:
		using difference_type = std::ptrdiff_t;
		using value_type = T;
		using pointer = T*;
		using reference = T&;
		using iterator_category = std::output_iterator_tag;

	private:
		T *cursor, *begin, *end;
		iterator(size_t ind, const vector& v): 
			cursor(v.buf+ind), begin(v.buf), end(v.buf+v.len) {}
		iterator(T* cursor, T* begin, T* end): 
			cursor(cursor), begin(begin), end(end) {}
	public:
		/// friends
		friend class vector<T>;
		/// return a new iterator which pointer n-next elements
		/// as well as operator-
		iterator operator+(const int &n) const 
		{
			T* ncursor=cursor+n;
			if(ncursor<begin) throw index_out_of_bound();
			if(ncursor>end) // iter::end
				return iterator(end, begin, end);
			return iterator(ncursor, begin, end);
		}
		iterator operator-(const int &n) const 
		{
			T* ncursor=cursor-n;
			if(ncursor<begin) throw index_out_of_bound();
			if(ncursor>end) // iter::end
				return iterator(end, begin, end);
			return iterator(ncursor, begin, end);
		}
		iterator& operator+=(const int &n) 
		{
			T* ncursor=cursor+n;
			if(ncursor<begin) throw index_out_of_bound();
			if(ncursor>end) cursor=end;
			else cursor=ncursor;
			return *this;
		}
		iterator& operator-=(const int &n) 
		{
			T* ncursor=cursor-n;
			if(ncursor<begin) throw index_out_of_bound();
			if(ncursor>end) cursor=end;
			else cursor=ncursor;
			return *this;
		}
		/// iter++
		iterator operator++(int) 
		{
			iterator ret=*this; // copy
			if(cursor<end) cursor++;
			return ret;
		}
		/// ++iter
		iterator& operator++() 
		{
			if(cursor<end) cursor++;
			return *this;
		}
		/// iter--, throw if this is iter::begin
		iterator operator--(int)
		{
			if(cursor==begin) throw index_out_of_bound();
			iterator ret=*this; // copy
			cursor--;
			return ret;
		}
		/// --iter
		iterator& operator--() 
		{
			if(cursor==begin) throw index_out_of_bound();
			cursor--;
			return *this;
		}
		// return the distance between two iterators,
		// if these two iterators point to different vectors, throw invaild_iterator.
		int operator-(const iterator &rhs) const 
		{
			if(buf!=rhs.buf) throw invalid_iterator();
			return cursor-rhs.cursor;
		}
		/// *iter
		T& operator*() const{
			if(cursor>=end) throw index_out_of_bound(); // iter::end
			return *cursor;
		}
		/// check whether two iterators are same (pointing to the same memory address).
		bool operator==(const iterator &rhs) const {return cursor==rhs.cursor;}
		bool operator==(const const_iterator &rhs) const {return cursor==rhs.cursor;}
		bool operator!=(const iterator &rhs) const {return cursor!=rhs.cursor;}
		bool operator!=(const const_iterator &rhs) const {return cursor!=rhs.cursor;}
	};

	/// iterator with immutable contents
	class const_iterator 
	{
	public:
		using difference_type = std::ptrdiff_t;
		using value_type = T;
		using pointer = T*;
		using reference = T&;
		using iterator_category = std::output_iterator_tag;

	private:
		T *cursor, *begin, *end;
		const_iterator(size_t ind, const vector& v): 
			cursor(v.buf+ind), begin(v.buf), end(v.buf+v.len) {}
		const_iterator(T* cursor, T* begin, T* end): 
			cursor(cursor), begin(begin), end(end) {}
	public:
		friend class vector<T>;
		/// return a new iterator which pointer n-next elements
		/// as well as operator-
		const_iterator operator+(const int &n) const 
		{
			T* ncursor=cursor+n;
			if(ncursor<begin) throw index_out_of_bound();
			if(ncursor>end) // iter::end
				return const_iterator(end, begin, end);
			return const_iterator(ncursor, begin, end);
		}
		const_iterator operator-(const int &n) const 
		{
			T* ncursor=cursor-n;
			if(ncursor<begin) throw index_out_of_bound();
			if(ncursor>end) // iter::end
				return const_iterator(end, begin, end);
			return const_iterator(ncursor, begin, end);
		}
		const_iterator& operator+=(const int &n) 
		{
			T* ncursor=cursor+n;
			if(ncursor<begin) throw index_out_of_bound();
			if(ncursor>end) cursor=end;
			else cursor=ncursor;
			return *this;
		}
		const_iterator& operator-=(const int &n) 
		{
			T* ncursor=cursor-n;
			if(ncursor<begin) throw index_out_of_bound();
			if(ncursor>end) cursor=end;
			else cursor=ncursor;
			return *this;
		}
		/// iter++
		const_iterator operator++(int) 
		{
			const_iterator ret=*this; // copy
			if(cursor<end) cursor++;
			return ret;
		}
		/// ++iter
		const_iterator& operator++() 
		{
			if(cursor<end) cursor++;
			return *this;
		}
		/// iter--, throw if this is iter::begin
		const_iterator operator--(int)
		{
			if(cursor==begin) throw index_out_of_bound();
			const_iterator ret=*this; // copy
			cursor--;
			return ret;
		}
		/// --iter
		const_iterator& operator--() 
		{
			if(cursor==begin) throw index_out_of_bound();
			cursor--;
			return *this;
		}
		// return the distance between two iterators,
		// if these two iterators point to different vectors, throw invaild_iterator.
		int operator-(const const_iterator &rhs) const 
		{
			if(buf!=rhs.buf) throw invalid_iterator();
			return cursor-rhs.cursor;
		}
		/// *iter
		const T& operator*() const{
			if(cursor>=end) throw index_out_of_bound(); // iter::end
			return *cursor;
		}
		/// check whether two iterators are same (pointing to the same memory address).
		bool operator==(const iterator &rhs) const {return cursor==rhs.cursor;}
		bool operator==(const const_iterator &rhs) const {return cursor==rhs.cursor;}
		bool operator!=(const iterator &rhs) const {return cursor!=rhs.cursor;}
		bool operator!=(const const_iterator &rhs) const {return cursor!=rhs.cursor;}
	};

private:
	T* buf;
	size_t len, cap;
public:
	vector():buf(nullptr), len(0), cap(0) {}
	vector(const vector &other):len(other.len), cap(other.cap) 
	{
		buf=(T*)malloc(cap*sizeof(T));
		if(!buf) throw runtime_error();
		memcpy(buf, other.buf, len*sizeof(T));
	}
	~vector() 
	{
		for(size_t i=0; i<len; i++) buf[i].~T();
		if(buf) free(buf);
	}
	
	/// copies `other` vector to this.
	vector &operator=(const vector &other) 
	{
		if(this->buf==other.buf) return *this;
		len=other.len;
		if(other.len>cap) // realloc
		{
			cap=other.len;
			delete []buf;
			buf=(T*)malloc(other.len*sizeof(T));
			if(!buf) throw runtime_error();
		}
		memcpy(buf, other.buf, len*sizeof(T));
		return *this;
	}
	/**
	 * assigns specified element with bounds checking
	 * throw index_out_of_bound if pos is not in [0, len)
	 */
	T & at(const size_t &pos) 
	{
		if(pos>=len) throw index_out_of_bound();
		return buf[pos];
	}
	const T & at(const size_t &pos) const 
	{
		if(pos>=len) throw index_out_of_bound();
		return buf[pos];
	}
	T & operator[](const size_t &pos) 
	{
		if(pos>=len) throw index_out_of_bound();
		return buf[pos];
	}
	const T & operator[](const size_t &pos) const 
	{
		if(pos>=len) throw index_out_of_bound();
		return buf[pos];
	}
	/// access the first element.
	/// throw container_is_empty if len == 0
	const T & front() const 
	{
		if(len==0) throw container_is_empty();
		return buf[0];
	}
	/// access the last element.
	/// throw container_is_empty if len == 0
	const T & back() const 
	{
		if(len==0) throw container_is_empty();
		return buf[len-1];
	}
	
	/// iterators

	iterator begin() 
	{
		return iterator(0, *this);
	}
	const_iterator cbegin() const 
	{
		return const_iterator(0, *this);
	}
	iterator end() 
	{
		return iterator(len, *this);
	}
	const_iterator cend() const
	{
		return const_iterator(len, *this);
	}
	/// checks whether the container is empty
	bool empty() const {return len==0;}
	/// returns the number of elements
	size_t size() const {return len;}
	/// clears the contents
	void clear() 
	{
		for(size_t i=0; i<len; i++)
			buf[i].~T();
		len=0;
	}
	/// inserts value at index ind.
	/// returns an iterator pointing to the inserted value.
	/// 
	/// behaviour: call T(&T) and move into vec[ind]
	iterator insert(const size_t &ind, const T &value) 
	{
		if (ind>len) throw index_out_of_bound();
		if(len==cap)
		{ // realloc
			if(cap==0) // new
			{
				cap=4;
				buf=(T*)malloc(cap*sizeof(T));
				if(!buf) throw runtime_error();
				new(buf+ind)T(value);
			} 
			else // not new
			{
				cap*=2;
				T* newbuf=(T*)malloc(cap*sizeof(T));
				if(!newbuf) throw runtime_error();
				memcpy(newbuf, buf, ind*sizeof(T));
				new(newbuf+ind)T(value);
				memcpy(newbuf+ind+1, buf+ind, (len-ind)*sizeof(T));
				free(buf);
				buf=newbuf;
			}
		}
		else
		{
			// cannot use memcpy on overlapped mem
			memmove(buf+ind+1, buf+ind, (len-ind)*sizeof(T));
			new(buf+ind)T(value);
		}
		// std::cout<<"insert finished!\n";
		len++;
		return iterator(ind, *this);
	}
	/// inserts value before pos
	/// returns an iterator pointing to the inserted value.
	iterator insert(iterator pos, const T &value) 
	{
		if(pos.begin!=buf) throw invalid_iterator();
		return insert(pos.cursor-buf, value);
	}
	
	///  removes the element with index ind.
	/// return an iterator pointing to the following element.
	iterator erase(const size_t &ind) 
	{
		if(ind>=len) throw index_out_of_bound();
		buf[ind].~T();
		len--;
		for(size_t i=ind; i<len; i++)
			buf[i]=buf[i+1];
		return iterator(ind, *this);
	}
	/// removes the element at pos.
	/// return an iterator pointing to the following element.
	iterator erase(iterator pos) 
	{
		if(pos.begin!=buf) throw invalid_iterator();
		return erase(pos.cursor-buf);
	}
	/// adds an element to the end.
	void push_back(const T &value) {insert(len, value);}
	/// remove the last element from the end.
	void pop_back() {erase(len-1);}
};
}

#endif
