#ifndef REVERSE_ITERATOR_HPP
#define REVERSE_ITERATOR_HPP

#include "common.hpp"
#include "iterator_traits.hpp"

namespace syu_reverse
{
	template<class Iterator>
	class Reverse_Iterator
	{
	private:
		Iterator it_;
		typedef IteratorTraits<Iterator> traits_type;

	private:
		typedef Reverse_Iterator<Iterator> self;
		typedef typename IteratorTraits<Iterator>::value_type value_type;
		typedef typename IteratorTraits<Iterator>::pointer    Pointer;
		typedef typename IteratorTraits<Iterator>::reference  Reference;

	public:
		Reverse_Iterator(Iterator it)
			: it_(it)
		{}

		Reference operator*()
		{
			Iterator prev = it_;
			return *--prev;
		}

		Pointer operator->()
		{
			return &operator*();
		}

		self& operator++()
		{
			--it_;  // 注意这里是减少
			return *this;
		}

		self operator++(int)
		{
			self tmp(it_);
			--it_;  // 注意这里是减少
			return tmp;
		}

		self& operator--()
		{
			++it_;  // 注意这里是增加
			return *this;
		}

		self operator--(int)
		{
			self tmp(it_);
			++it_;  // 注意这里是增加
			return tmp;
		}


		bool operator!= (const self& rit) const
		{
			return it_ != rit.it_;
		}

	};
}

#endif // REVERSE_ITERATOR_HPP
