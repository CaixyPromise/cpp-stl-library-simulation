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
	typedef typename Iterator::difference_type difference_type;  // 萃取迭代器的差异类型
	typedef typename Iterator::iterator_category iterator_category;  // 萃取迭代器的类别
	IteratorTraits() = default;
};

// 针对原生指针的特化萃取
template<typename T>
struct IteratorTraits<T*>
{
	typedef T value_type;
	typedef T* pointer;
	typedef T& reference;
	typedef std::ptrdiff_t difference_type;  // 对于原生指针，差异类型是ptrdiff_t
	typedef std::random_access_iterator_tag iterator_category;  // 原生指针是随机访问迭代器
	IteratorTraits() = default;
};

// 用于处理常量原生指针作为迭代器的情况。这与非常量原生指针相似，但所有的类型都是常量。
template<typename T>
struct IteratorTraits<const T*>
{
	typedef T value_type;
	typedef const T* pointer;
	typedef const T& reference;
	typedef std::ptrdiff_t difference_type;  
	typedef std::random_access_iterator_tag iterator_category;  // 常量原生指针是随机访问迭代器
	IteratorTraits() = default;
};

#endif // ITERATOR_TRAITS_HPP