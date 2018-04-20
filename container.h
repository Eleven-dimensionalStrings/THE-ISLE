#pragma once
#include <initializer_list>
namespace my_container
{

	template<class T>
	class my_vector
	{
	private:
		T * val;
		std::size_t vsize;
		std::size_t vmsize;
	public:
		//ini
		my_vector() :val(nullptr), vsize(0), vmsize(0)
		{
		}
		explicit my_vector(std::size_t tsize) :val(new T[tsize]), vsize(tsize), vmsize(tsize)
		{

		}
		explicit my_vector(std::size_t tsize, const T& val) :val(new T[tsize]), vsize(tsize), vmsize(tsize)
		{
			for (auto&i : *this)
			{
				i = val;
			}
		}
		my_vector(std::initializer_list<T> ini)
		{

		}

		//iterator
		class iterator
		{
		public:
			iterator(T* begin, T* now, T* end) :_begin(begin), _now(now), _end(end)
			{

			}
			iterator(const iterator&t) :_begin(t._begin), _now(t._now), _end(t._end)
			{

			}
			iterator& operator++()
			{
				++_now;
				return *this;
			}
			iterator operator++(int)
			{
				++_now;
				return iterator(_begin, _now - 1, _end);
			}
			iterator& operator--()
			{
				--_now;
				return *this;
			}
			iterator operator--(int)
			{
				--_now;
				return iterator(_begin, _now + 1, _end);
			}
			bool operator==(const iterator& other)const
			{
				if (_now != _other._now)return 0;
				if (_begin != _other._begin)return 0;
				if (_end != _other._end)return 0;
				return 1;
			}
			bool operator!=(const iterator& other)const
			{
				//maybe should check something on _DEBUG
				return _now != other._now;
			}
			T& operator*()
			{
#ifdef _DEBUG
				if (_now < _begin || _now >= _end)
				{
					throw std::out_of_range("iterator out of range");
				}
#endif // _DEBUG
				return *_now;
			}
		private:
			T * _begin, *_now, *_end;
		};

		class const_iterator
		{
		public:
			const_iterator(T* begin, T* now, T* end) :_begin(begin), _now(now), _end(end)
			{

			}
			const_iterator(const const_iterator&t) :_begin(t._begin), _now(t._now), _end(t._end)
			{

			}
			const_iterator& operator++()
			{
				++_now;
				return *this;
			}
			const_iterator operator++(int)
			{
				++_now;
				return iterator(_begin, _now - 1, _end);
			}
			const_iterator& operator--()
			{
				--_now;
				return *this;
			}
			const_iterator operator--(int)
			{
				--_now;
				return iterator(_begin, _now + 1, _end);
			}
			bool operator==(const const_iterator& other)const
			{
				if (_now != _other._now)return 0;
				if (_begin != _other._begin)return 0;
				if (_end != _other._end)return 0;
				return 1;
			}
			bool operator!=(const const_iterator& other)const
			{
				//maybe should check something on _DEBUG
				return _now != other._now;
			}
			const T& operator*()const
			{
#ifdef _DEBUG
				if (_now < _begin || _now >= _end)
				{
					throw std::out_of_range("iterator out of range");
				}
#endif // _DEBUG
				return *_now;
			}
		private:
			T * _begin, *_now, *_end;
		};
		class reverse_iterator
		{
		public:
			reverse_iterator(T* rbegin, T* now, T* rend) :_rbegin(rbegin), _now(now), _rend(rend)
			{

			}
			reverse_iterator(const reverse_iterator&t) :_rbegin(t._rbegin), _now(t._now), _rend(t._rend)
			{

			}
			reverse_iterator& operator++()
			{
				--_now;
				return *this;
			}
			reverse_iterator operator++(int)
			{
				--_now;
				return iterator(_rbegin, _now + 1, _rend);
			}
			reverse_iterator& operator--()
			{
				++_now;
				return *this;
			}
			reverse_iterator operator--(int)
			{
				++_now;
				return iterator(_rbegin, _now - 1, _rend);
			}
			bool operator==(const reverse_iterator& other)const
			{
				if (_now != _other._now)return 0;
				if (_rbegin != _other._rbegin)return 0;
				if (_rend != _other._rend)return 0;
				return 1;
			}
			bool operator!=(const reverse_iterator& other)const
			{
				//maybe should check something on _DEBUG
				return _now != other._now;
			}
			T& operator*()
			{
#ifdef _DEBUG
				if (_now > _rbegin || _now <= _rend)
				{
					throw std::out_of_range("iterator out of range");
				}
#endif // _DEBUG
				return *_now;
			}
		private:
			T * _rbegin, *_now, *_rend;
		};
		iterator begin()
		{
			return iterator(val, val, val + vsize);
		}
		iterator end()
		{
			return iterator(val, val + vsize, val + vsize);
		}
		reverse_iterator rbegin()
		{
			return reverse_iterator(val + vsize - 1, val + vsize - 1, val - 1);
		}
		reverse_iterator rend()
		{
			return reverse_iterator(val + vsize - 1, val - 1, val - 1);
		}

		//revise
		void push_back(const T& val)
		{

		}
		void insert(iterator i, const T& val)
		{

		}

		//access
		T& operator[](std::size_t pos)
		{
#ifdef _DEBUG
			if (pos < 0 || pos >= vsize)
				throw out_of_range("my_vector out of range");
#endif // _DEBUG
			return *(val + pos);
		}

		//capacity
		std::size_t size()const
		{
			return vsize;
		}
	};
}