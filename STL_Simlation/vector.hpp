#include "common.hpp"


namespace syu_vec
{
	template<class T>
	class vector
	{
	private:
		// Vector�ĵ�������һ��ԭ��ָ��
		typedef T* iterator;
		typedef const T* const_iterator;

		typedef Reverse_Iterator<iterator> reverse_iterator;
		typedef Reverse_Iterator<const_iterator> const_reverse_iterator;

	private:
		iterator _start; // ָ�����ݿ�Ŀ�ʼ
		iterator _finish; // ָ����Ч���ݵ�β
		iterator _end_Of_Storage; // ָ��洢������β

	public:
		iterator begin()
		{
			return _start;
		}
		iterator end()
		{
			return _finish;
		}

		const_iterator begin() const
		{
			return _start;
		}
		const_iterator end() const
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

		reverse_iterator rbegin()
		{
			return reverse_iterator(end());
		}

		reverse_iterator rend()
		{
			return reverse_iterator(begin());
		}

		const_reverse_iterator crbegin() const
		{
			return const_reverse_iterator(end());
		}

		const_reverse_iterator crend() const
		{
			return const_reverse_iterator(begin());
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
					// ������memcpy, ��Ϊmemcpy������һ��ǳ������ֻ�ǵ�������ֵ��ȥ
					// ������Զ������ͣ���ô����������delete[] startʱ����������������Ӷ����ܷ���Ұָ������
					// ������������ͣ���ôû����
					// ���������Ǳ���Ҫʹ��һ������ֵ�����
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
			if (n < capacity) // �������������Ҫ���Ĵ�С��ֱ�����ݾ��У�����finishλ�ã������·���ռ䣩
			{
				_finish = _start + n;
			}
			else
			{
				// ���Ҫ���Ŀռ���ڵ�ǰ����������
				if (n > capacity())
				{
					reserve(n);
				}

				// �������
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

	void test_reverse_iterators()
	{
		vector<int> v;
		for (int i = 0; i < 5; ++i)
		{
			v.push_back(i);
		}

		// ���Է�const reverse_iterator
		auto rit = v.rbegin();
		auto rend = v.rend();

		int expected_value = 4;
		while (rit != rend)
		{
			int ref_val = *rit;
			assert(ref_val == expected_value);
			++rit;
			--expected_value;
		}

		// ����--��++������
		--rit;
		expected_value = 0;
		while (rit != v.rbegin())
		{
			int ref_val = *rit;
			assert(ref_val == expected_value);
			--rit;
			++expected_value;
		}

		// ���� const_reverse_iterator
		auto crit = v.crbegin();
		auto crend = v.crend();

		expected_value = 4;
		while (crit != crend)
		{
			assert(*crit == expected_value);
			++crit;
			--expected_value;
		}

	}

	void test_Algorithm()
	{

	}


	void callTestFunction()
	{
		test_default_constructor_and_push_back();
		output_log("vector", "test_default_constructor_and_push_back passed!");

		test_size_constructor();
		output_log("vector", "test_size_constructor passed!");

		test_range_constructor();
		output_log("vector", "test_range_constructor passed!");

		test_copy_constructor();
		output_log("vector", "test_copy_constructor passed!");

		test_assignment_operator();
		output_log("vector", "test_assignment_operator passed!");

		test_iterators();
		output_log("vector", "test_iterators passed!");

		test_reverse_iterators();
		output_log("vector", "test_reverse_iterators in vector passed!");

		output_log("vector", "All vector tests passed!");
		return;
	}
}
