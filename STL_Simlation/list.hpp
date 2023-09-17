#include "common.hpp"



namespace syu_list
{
	template<class T>
	struct ListNode
	{
		ListNode<T>* _prev;
		ListNode<T>* _next;
		T _val;
		
		ListNode(ListNode<T>* prev = nullptr, ListNode<T>* next = nullptr, T val = T())
			: _val(val)
			, _prev(prev)
			, _next(next)
		{}

		ListNode(T val)
			: _val(val)
		{}


		bool operator==(const ListNode& v) const
		{
			return v._val == _val;
		}

		bool operator!=(const ListNode& v) const
		{
			return v._val != _val;
		}

		bool operator>(const ListNode& v) const
		{
			return v._val > _val;
		}

		bool operator<(const ListNode& v) const
		{
			return v._val < _val;
		}
		bool operator>=(const ListNode& v) const
		{
			return v._val >= _val;
		}

		bool operator<=(const ListNode& v) const
		{
			return v._val <= _val;
		}
	};

	// Reference == &, Pointer == *
	template<class T, class Ref, class Ptr>
	class __list_iterator
	{
	public:
		typedef ListNode<T> Node;
		typedef __list_iterator<T, Ref, Ptr> self;
		typedef Ref Reference;
		typedef Ptr Pointer;
		typedef T value_type;

		Node* _node;
	public:
		__list_iterator(Node* node)
			:_node(node)
		{}

		Ref operator*()
		{
			return _node->_val;
		}

		Ptr operator->()
		{
			return &_node->_val;
		}
		// ++it 
		self& operator++()
		{
			_node = _node->_next;
			return *this;
		}
		// it++ ->生成一个拷贝，再自己node->next, 返回拷贝（先++后使用）
		self operator++(int)
		{
			self tmp(*this);
			_node = _node->_next;
			return tmp;
		}
		// --it;
		self& operator--()
		{
			_node = _node->_prev;
			return *this;
		}
		// it--;
		self operator--(int)
		{
			self tmp(*this);
			_node = _node->_prev;
			return tmp;
		}
		
		bool operator==(const self& v) const
		{
			return _node == v._node;
		}

		bool operator!=(const self& v) const
		{
			return _node != v._node;
		}
	};

	template<class T>
	class list
	{
	private:
		typedef ListNode<T> Node;
		Node* _head;
	private:
		void __init__()
		{
			_head = new Node();
			_head->_next = _head;
			_head->_prev = _head;
		}
	public:
		typedef __list_iterator<T, T&, T*> iterator;
		typedef __list_iterator<T, const T&, const T*> const_iterator;

		typedef Reverse_Iterator<iterator> reverse_iterator;
		typedef Reverse_Iterator<const_iterator> const_reverse_iterator;


		// 迭代器的返回值的应该参考 insert、push_back和push_front的设计思路
		// 这3个都是前插操作
		iterator begin()
		{
			return iterator(_head->_next);
		}
		
		iterator end()
		{
			return iterator(_head);
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

		const_iterator begin() const
		{
			return const_iterator(_head->_next);
		}

		const_iterator end() const
		{
			return const_iterator(_head);
		}

		list()
		{
			__init__();
		}

		list(int size, const T& val = T())
		{
			__init__();
			for (int i = 0; i < size; ++i)
			{
				push_back(val);
			}
		}

		template<class InputIterator>
		list(InputIterator first, InputIterator last)
		{
			__init__();
			while (first != last)
			{
				push_back(*first);
				++first;
			}
		}

		list(list<T>& _lt)
		{
			__init__();
			list<T> tmp(begin(), end());
			swap(_lt);
		}


		list<T>& operator=(list<T>& _lt)
		{
			swap(_lt);
			return *this;
		}

		void swap(list<T>& _lt)
		{
			std::swap(_head, _lt._head);
		}


		~list()
		{
			clear();
			delete _head;
			_head = nullptr;
		}


		iterator push_back(const T& val)
		{
			return insert(end(), val);
		}

		iterator push_front(const T& val)
		{
			return insert(begin(), val);
		}

		iterator pop_back()
		{
			return erase(--end());
		}
		
		iterator pop_front()
		{
			return erase(begin());
		}


		iterator insert(iterator pos, const T& value)
		{
			Node* newnode = new Node(value);
			Node* curr = pos._node;
			Node* prev = pos._node->_prev;

			prev->_next = newnode;
			newnode->_prev = prev;
			newnode->_next = curr;
			curr->_prev = newnode;
			return iterator(newnode);
		}

		iterator erase(iterator pos)
		{
			assert(pos != end());
			Node* prev = pos._node->_prev;
			Node* next = pos._node->_next;

			delete pos._node;

			prev->_next = next;
			next->_prev = prev;
			return iterator(next);
		}

		void clear()
		{
			iterator it = begin();
			while (it != end())
			{
				erase(it++);
			}
		}
	};

}


namespace Test_list
{
	using namespace syu_list;

	void test_default_constructor()
	{
		list<int> l;
		assert(l.begin() == l.end()); // The list should be empty.
	}

	void test_size_constructor() 
	{
		list<int> l(5, 10);
		auto it = l.begin();
		for (int i = 0; i < 5; ++i) 
		{
			assert(*it == 10);
			++it;
		}
	}

	void test_range_constructor() 
	{
		list<int> l1;
		for (int i = 0; i < 5; ++i) 
		{
			l1.push_back(i);
		}

		list<int> l2(l1.begin(), l1.end());
		auto it1 = l1.begin();
		auto it2 = l2.begin();
		while (it1 != l1.end() && it2 != l2.end()) 
		{
			assert(*it1 == *it2);
			++it1;
			++it2;
		}
	}

	void test_copy_constructor() 
	{
		list<int> l1;
		for (int i = 0; i < 5; ++i)
		{
			l1.push_back(i);
		}

		list<int> l2(l1);
		auto it1 = l1.begin();
		auto it2 = l2.begin();
		while (it1 != l1.end() && it2 != l2.end()) 
		{
			assert(*it1 == *it2);
			++it1;
			++it2;
		}
	}

	void test_assignment_operator() 
	{
		list<int> l1;
		for (int i = 0; i < 5; ++i) 
		{
			l1.push_back(i);
		}

		list<int> l2;
		l2 = l1;

		auto it1 = l1.begin();
		auto it2 = l2.begin();
		while (it1 != l1.end() && it2 != l2.end()) 
		{
			assert(*it1 == *it2);
			++it1;
			++it2;
		}
	}

	void test_modifiers() 
	{
		list<int> l;
		l.push_back(1);
		l.push_back(2);
		l.push_back(3);
		l.push_front(0);
		assert(*l.begin() == 0);
		assert(*(++l.begin()) == 1);

		l.pop_back();
		assert(*(--l.end()) == 2);

		l.pop_front();
		assert(*l.begin() == 1);

		auto it = l.begin();
		++it;
		l.insert(it, 4);
		assert(*it == 2);
		assert(*(--it) == 4);

		it = l.erase(it);
		assert(*it == 2);
	}

	void test_iterators() 
	{
		list<int> l;
		l.push_back(1);
		l.push_back(2);
		l.push_back(3);

		auto it = l.begin();
		assert(*it == 1);
		++it;
		assert(*it == 2);
		--it;
		assert(*it == 1);
	}

	void test_reverse_iterators()
	{
		list<int> l;
		for (int i = 0; i < 5; ++i)
		{
			l.push_back(i);
		}

		// Test non-const reverse_iterator
		auto rit = l.rbegin();
		auto rend = l.rend();

		int expected_value = 4;
		while (rit != rend)
		{
			assert(*rit == expected_value);
			++rit;
			--expected_value;
		}

		// Test operator-- and operator++
		--rit;
		expected_value = 0;
		while (rit != rend)
		{
			assert(*rit == expected_value);
			--rit;
			++expected_value;
		}

		// Test const_reverse_iterator
		auto crit = l.crbegin();
		auto crend = l.crend();

		expected_value = 4;
		while (crit != crend)
		{
			assert(*crit == expected_value);
			++crit;
			--expected_value;
		}
	}

	void callTestFunction()
	{
		test_default_constructor();
		output_log("list", "test_default_constructor passed!");

		test_size_constructor();
		output_log("list", "test_size_constructor passed!");

		test_range_constructor();
		output_log("list", "test_range_constructor passed!");

		test_copy_constructor();
		output_log("list", "test_copy_constructor passed!");

		test_assignment_operator();
		output_log("list", "test_assignment_operator passed!");

		test_modifiers();
		output_log("list", "test_modifiers passed!");

		test_iterators();
		output_log("list", "test_iterators passed!");
		test_reverse_iterators();
		output_log("list", "test_reverse_iterators passed!");

		output_log("list", "All list tests passed!");
	}
}