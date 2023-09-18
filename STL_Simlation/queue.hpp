#ifndef QUEUE_HPP
#define QUEUE_HPP
#include <deque>
#include <cassert>
#include "common.hpp"

namespace syu_queue
{
#ifndef __STL_LIMITED_DEFAULT_TEMPLATES
	template <class T, class Sequence = deque<T> >
#else
	template <class T, class Sequence>
#endif
	class queue
	{
	public:
		typedef typename Sequence::value_type value_type;
		typedef typename Sequence::size_type size_type;
		typedef typename Sequence::reference reference;
		typedef typename Sequence::const_reference const_reference;
	protected:
		Sequence _container;
	public:
		queue() = default;


		void push(const T& x)
		{
			_container.push_back(x);
		}

		void pop()
		{
			assert(!_container.empty());
			_container.pop_front();
		}

		T& back()
		{
			assert(!_container.empty());
			return _container.back();
		}

		const T& back() const
		{
			assert(!_container.empty());
			return _container.back();
		}

		T& front()
		{
			assert(!_container.empty());
			return _container.front();
		}

		const T& front() const
		{
			assert(!_container.empty());
			return _container.front();
		}

		size_t size()const
		{
			return _container.size();
		}

		bool empty()const
		{
			return _container.empty();
		}
	};
}

namespace Test_Queue
{
	using namespace syu_queue;

	void test_push_pop_front_back() 
	{
		queue<int> q;

		// 最初，队列应该是空的。
		assert(q.empty());

		output_log("queue", "Initially, the queue should be empty.");

		q.push(1);
		assert(q.front() == 1);
		assert(q.back() == 1);

		q.push(2);
		assert(q.front() == 1);
		assert(q.back() == 2);

		q.push(3);
		assert(q.front() == 1);
		assert(q.back() == 3);

		output_log("queue", "Push elements and test front and back");

		q.pop();
		assert(q.front() == 2);
		assert(q.back() == 3);

		q.pop();
		assert(q.front() == 3);
		assert(q.back() == 3);

		q.pop();
		assert(q.empty());
		output_log("queue", "Pop elements and test front and back");

	}

	void callTestFunction() {
		test_push_pop_front_back();
		output_log("queue", "All queue tests passed!");
	}
}



#endif // !QUEUE_HPP
