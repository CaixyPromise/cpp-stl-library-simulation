#pragma once
#include <iostream>
#include <assert.h>
using namespace std;

namespace syu_vec
{
	template<class T>
	class vector
	{
	public:
		// Vector的迭代器是一个原生指针
		typedef T* iterator;
		typedef const T* const_iterator;
	private:
		iterator _start; // 指向数据块的开始
		iterator _finish; // 指向有效数据的尾
		iterator _end_Of_Storage; // 指向存储容量的尾

	public:
		iterator begin()
		{
			return _start;
		}
		iterator end()
		{
			return _finish;
		}

		const_iterator cbegin() const
		{
			return _start;
		}
		const_iterator cend() const
		{
			return _finish;
		}

		// construct and destroy
		vector()
			: _start(nullptr)
			, _finish(nullptr)
			, _end_Of_Storage(nullptr)
		{}

		vector(int n, const T& value = T())
			: _start(nullptr)
			, _finish(nullptr)
			, _end_Of_Storage(nullptr)
		{
			for (int i = 0; i < n; i++)
			{
				push_back(value);
			}
		}
		template<class InputIterator>
		vector(InputIterator first, InputIterator last)
			: _start(nullptr)
			, _finish(nullptr)
			, _end_Of_Storage(nullptr)
		{
			reserve((last - first) * sizeof(T));
			while (first != last)
			{
				push_back(*first);
				first++;
			}
		}

		vector(const vector<T>& v)
			:_start(nullptr)
			, _finish(nullptr)
			, _end_Of_Storage(nullptr)
		{
			vector<T> tmp(v.cbegin(), v.cend());
			swap(tmp);
		}

		vector<T>& operator=(vector<T> v)
		{
			this->swap(v);
			return *this;
		}

		~vector()
		{
			if (_start)
			{
				delete[] _start;
				_start = _finish = _end_Of_Storage = nullptr;
			}
		}

		// capacity
		size_t size() const
		{
			return _finish - _start;
		}

		size_t capacity() const
		{
			return _end_Of_Storage - _start;
		}

		void reserve(size_t n)
		{
			if (n > capacity())
			{
				T* tmp = new T[n];
				if (_start)
				{
					// 不能用memcpy, 因为memcpy本质是一个浅拷贝，只是单纯拷贝值过去
					// 如果是自定义类型，那么在下面清理delete[] start时会调用析构函数，从而可能发生野指针问题
					// 如果是内置类型，那么没问题
					// 所以这里是必须要使用一个个赋值的深拷贝
					//memcpy(tmp, _start, size() * sizeof(T));
					for (int i = 0; i < size(); i++)
					{
						tmp[i] = _start[i];
					}
				}
				_finish = tmp + size();
				_end_Of_Storage = tmp + n;
				delete[] _start;
				_start = tmp;
			}
		}

		void resize(size_t n, const T& value = T())
		{
			if (n < capacity) // 如果容量大于需要填充的大小，直接缩容就行（调整finish位置，不重新分配空间）
			{
				_finish = _start + n;
			}
			else
			{
				// 如果要填充的空间大于当前容量，扩容
				if (n > capacity())
				{
					reserve(n);
				}

				// 填充数据
				while (_finish != _start + n)
				{
					*_finish = value;
					_finish++;
				}
			}
		}

		///////////////access///////////////////////////////
		T& operator[](size_t pos)
		{
			return _start[pos];
		}
		const T& operator[](size_t pos) const
		{
			return _start[pos];
		}

		///////////////modify/////////////////////////////
		void push_back(const T& x)
		{
			insert(end(), x);
		}

		void pop_back()
		{
			erase(end());
		}

		void swap(vector<T>& v)
		{
			std::swap(_start, v._start);
			std::swap(_finish, v._finish);
			std::swap(_end_Of_Storage, v._end_Of_Storage);
		}

		iterator insert(iterator pos, const T& x)
		{
			assert(pos >= _start);
			assert(pos <= _finish);

			if (_finish == _end_Of_Storage)
			{
				size_t length = pos - _start;
				reserve(capacity() == 0 ? 4 : capacity() * 2);
				pos = _start + length;
			}
			iterator _end = end() - 1;
			while (pos < _end)
			{
				*(_end + 1) = *_end;
				_end--;
			}
			*pos = x;
			_finish++;
			return pos;
		}

		iterator erase(iterator pos)
		{
			assert(pos >= _start);
			assert(pos <= _finish);
			iterator cur = pos + 1;
			while (cur < _finish)
			{
				*(cur - 1) = *cur;
				cur++;
			}
			_finish--;
			return pos;
		}
	};

	template<class T>
	void print(const char* name, T& con)
	{
		std::cout << name << ": ";

		for (auto it = con.begin(); it != con.end(); ++it)
		{
			std::cout << *it << " ";
		}
		std::cout << std::endl;
	}
};


namespace Test_Vector
{
	using namespace syu_vec;
	void test_default_constructor_and_push_back() 
	{
		vector<int> v;
		assert(v.begin() == v.end()); // Initially, the vector should be empty.

		v.push_back(1);
		v.push_back(2);
		v.push_back(3);

		assert(*v.begin() == 1);
		assert(*(v.end() - 1) == 3);
	}

	void test_size_constructor() 
	{
		vector<int> v(5, 10);

		for (auto it = v.begin(); it != v.end(); ++it) 
		{
			assert(*it == 10);
		}
	}

	void test_range_constructor()
	{
		vector<int> v1;
		v1.push_back(1);
		v1.push_back(2);
		v1.push_back(3);

		vector<int> v2(v1.cbegin(), v1.cend());

		auto it1 = v1.begin();
		auto it2 = v2.begin();
		for (; it1 != v1.end() && it2 != v2.end(); ++it1, ++it2)
		{
			assert(*it1 == *it2);
		}
	}

	void test_copy_constructor() 
	{
		vector<int> v1;
		v1.push_back(1);
		v1.push_back(2);
		v1.push_back(3);

		vector<int> v2(v1);

		auto it1 = v1.begin();
		auto it2 = v2.begin();
		for (; it1 != v1.end() && it2 != v2.end(); ++it1, ++it2) 
		{
			assert(*it1 == *it2);
		}
	}

	void test_assignment_operator() 
	{
		vector<int> v1;
		v1.push_back(1);
		v1.push_back(2);
		v1.push_back(3);

		vector<int> v2;
		v2 = v1;

		auto it1 = v1.begin();
		auto it2 = v2.begin();
		for (; it1 != v1.end() && it2 != v2.end(); ++it1, ++it2) 
		{
			assert(*it1 == *it2);
		}
	}

	void test_iterators() 
	{
		vector<int> v;
		v.push_back(1);
		v.push_back(2);
		v.push_back(3);

		assert(*v.begin() == 1);
		assert(*(v.end() - 1) == 3);
		assert(*v.cbegin() == 1);
		assert(*(v.cend() - 1) == 3);
	}

	void callTestFunction()
	{
		test_default_constructor_and_push_back();
		std::cout << "Test: test_default_constructor_and_push_back passed!" << std::endl;

		test_size_constructor();
		std::cout << "Test: test_size_constructor passed!" << std::endl;

		test_range_constructor();
		std::cout << "Test: test_range_constructor passed!" << std::endl;

		test_copy_constructor();
		std::cout << "Test: test_copy_constructor passed!" << std::endl;

		test_assignment_operator();
		std::cout << "Test: test_assignment_operator passed!" << std::endl;

		test_iterators();
		std::cout << "Test: test_iterators passed!" << std::endl;

		std::cout << "All vector tests passed!" << std::endl;
		return;
	}
}


/*
#pragma once
#include <iostream>
#include <assert.h>

namespace ContainerVc
{
	template<class T>
	class vector
	{
	public:
		typedef T* iterator;
		typedef const T* const_iterator;

		vector()
			:_start(nullptr)
			, _finish(nullptr)
			, _endofstorage(nullptr)
		{}

		template <class InputIterator>
		vector(InputIterator first, InputIterator last)
			:_start(nullptr)
			, _finish(nullptr)
			, _endofstorage(nullptr)
		{
			while (first != last)
			{
				push_back(*first);
				++first;
			}
		}

		void swap(vector<T>& v)
		{
			std::swap(_start, v._start);
			std::swap(_finish, v._finish);
			std::swap(_endofstorage, v._endofstorage);
		}

		vector(const vector<T>& v)
			:_start(nullptr)
			, _finish(nullptr)
			, _endofstorage(nullptr)
		{
			vector<T> tmp(v.begin(), v.end());
			swap(tmp);
		}

		vector<T>& operator=(vector<T> v)
		{
			swap(v);
			return *this;
		}

		~vector()
		{
			if (_start)
			{
				delete[] _start;
				_start = _finish = _endofstorage = nullptr;
			}
		}

		const_iterator begin() const
		{
			return _start;
		}

		const_iterator end() const
		{
			return _finish;
		}

		iterator begin()
		{
			return _start;
		}

		iterator end()
		{
			return _finish;
		}

		const T& operator[](size_t i) const
		{
			assert(i < size());
			return _start[i];
		}

		T& operator[](size_t i)
		{
			assert(i < size());
			return _start[i];
		}

		size_t size() const
		{
			return _finish - _start;
		}

		size_t capacity() const
		{
			return _endofstorage - _start;
		}

		void reserve(size_t n)
		{
			if (n > capacity())
			{
				size_t sz = size();
				T* tmp = new T[n];
				if (_start)
				{
					for (size_t i = 0; i < sz; ++i)
					{
						tmp[i] = _start[i];
					}

					delete[] _start;
				}
				_start = tmp;
				_finish = _start + sz;
				_endofstorage = _start + n;
			}
		}

		void resize(size_t n, const T& val = T())
		{
			if (n < size())
			{
				_finish = _start + n;
			}
			else
			{
				if (n > capacity())
				{
					reserve(n);
				}

				while (_finish != _start + n)
				{
					*_finish = val;
					++_finish;
				}
			}
		}

		iterator insert(iterator pos, const T& x)
		{
			assert(pos >= _start);
			assert(pos <= _finish);

			if (_finish == _endofstorage)
			{
				size_t len = pos - _start;
				reserve(capacity() == 0 ? 4 : capacity() * 2);
				pos = _start + len;
			}

			iterator end = _finish - 1;
			while (end >= pos)
			{
				*(end + 1) = *end;
				--end;
			}
			*pos = x;
			++_finish;

			return pos;
		}

		iterator erase(iterator pos)
		{
			assert(pos >= _start);
			assert(pos < _finish);

			iterator begin = pos + 1;
			while (begin < _finish)
			{
				*(begin - 1) = *begin;
				++begin;
			}

			--_finish;

			return pos;
		}

		void push_back(const T& x)
		{
			if (_finish == _endofstorage)
			{
				reserve(capacity() == 0 ? 4 : capacity() * 2);
			}
			*_finish = x;
			++_finish;
		}

		void pop_back()
		{
			assert(_finish > _start);

			--_finish;
		}
	private:
		iterator _start;
		iterator _finish;
		iterator _endofstorage;
	};
}
*/