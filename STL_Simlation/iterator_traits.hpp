#ifndef ITERATOR_TRAITS_HPP
#define ITERATOR_TRAITS_HPP

// 类型萃取器
// 针对萃取自定义类型
template<typename Iterator>
struct IteratorTraits
{
	/*
	value_type: 迭代器指向的元素类型。
	pointer: 迭代器内部用于指向元素的指针类型。
	reference: 迭代器用于引用元素的引用类型。
	这些类型都会在自定义迭代器中明确指定。
	*/
	typedef typename Iterator::value_type value_type;	// 萃取迭代器指向元素的类型
	typedef typename Iterator::Pointer    pointer;		// 萃取迭代器的指针类型
	typedef typename Iterator::Reference  reference;	// 萃取迭代器的引用类型
};

// 针对原生指针的特化萃取
template<typename T>
struct IteratorTraits<T*>
{
	typedef T value_type;
	typedef T* pointer;
	typedef T& reference;

	IteratorTraits() = default;
};

// 用于处理常量原生指针作为迭代器的情况。这与非常量原生指针相似，但所有的类型都是常量。
template<typename T>
struct IteratorTraits<const T*>
{
	typedef T value_type;
	typedef const T* pointer;
	typedef const T& reference;
};

#endif // ITERATOR_TRAITS_HPP