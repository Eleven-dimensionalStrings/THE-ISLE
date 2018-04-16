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
	public:
		//ini
		vector() :val(nullptr), vsize(0)
		{
		}
		explicit vector(std::size_t tsize) :val(new T[tsize]), vsize(tsize)
		{

		}
		explicit vector(std::size_t tsize, const T& val)
		{

		}
		vector(std::initializer_list<T> ini)
		{

		}
		//iterator
		class iterator
		{
		public:
			iterator(T* begin, T* now, T* end) :_begin(begin), _now(now), _end(end)
			{

			}
		private:
			T * _begin, * _now, * _end;
		};
		class const_iterator
		{
		public:

		private:
			const T * _begin, * _now, * _end;
		};
		class reverse_iterator
		{
		public:

		private:
			T * _begin, *_now, *_end;

		};
		//insert and push
		void push_back(T&& val)
		{

		}
		void insert(typename my_vector<T>::iterator i,const T& val)
		{
			
		}
	};
}