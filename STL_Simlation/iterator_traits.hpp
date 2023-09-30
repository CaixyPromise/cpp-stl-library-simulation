#ifndef ITERATOR_TRAITS_HPP
#define ITERATOR_TRAITS_HPP

// ������ȡ��
// �����ȡ�Զ�������
template<typename Iterator>
struct IteratorTraits
{
	/*
	value_type: ������ָ���Ԫ�����͡�
	pointer: �������ڲ�����ָ��Ԫ�ص�ָ�����͡�
	reference: ��������������Ԫ�ص��������͡�
	��Щ���Ͷ������Զ������������ȷָ����
	*/
	typedef typename Iterator::value_type value_type;	// ��ȡ������ָ��Ԫ�ص�����
	typedef typename Iterator::Pointer    pointer;		// ��ȡ��������ָ������
	typedef typename Iterator::Reference  reference;	// ��ȡ����������������
	typedef typename Iterator::difference_type difference_type;  // ��ȡ�������Ĳ�������
	typedef typename Iterator::iterator_category iterator_category;  // ��ȡ�����������
	IteratorTraits() = default;
};

// ���ԭ��ָ����ػ���ȡ
template<typename T>
struct IteratorTraits<T*>
{
	typedef T value_type;
	typedef T* pointer;
	typedef T& reference;
	typedef std::ptrdiff_t difference_type;  // ����ԭ��ָ�룬����������ptrdiff_t
	typedef std::random_access_iterator_tag iterator_category;  // ԭ��ָ����������ʵ�����
	IteratorTraits() = default;
};

// ���ڴ�����ԭ��ָ����Ϊ�����������������ǳ���ԭ��ָ�����ƣ������е����Ͷ��ǳ�����
template<typename T>
struct IteratorTraits<const T*>
{
	typedef T value_type;
	typedef const T* pointer;
	typedef const T& reference;
	typedef std::ptrdiff_t difference_type;  
	typedef std::random_access_iterator_tag iterator_category;  // ����ԭ��ָ����������ʵ�����
	IteratorTraits() = default;
};

#endif // ITERATOR_TRAITS_HPP