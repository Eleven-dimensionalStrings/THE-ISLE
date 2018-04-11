#pragma once
#include <initializer_list>
namespace my_container
{
	template<class T>
	class my_vector
	{
	public:
		//ini
		vector()
		{
		}
		explicit vector(std::size_t tsize)
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
			iterator(T* p) :ptr(p)
			{

			}
		private:
			T * ptr;
		};
		class const_iterator
		{
		public:
		private:
			const T* ptr;
		};
		class reverse_iterator
		{

		};
		//insert and push
		void push_back(T&& val)
		{

		}
		void insert(const_iterator)
		{

		}
	};
}