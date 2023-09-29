#include "common.hpp"
#include "iterator_traits.hpp"

namespace Simple_Algorithm
{
	template<typename T>
	typename std::remove_reference<T>::type&& move(T&& arg)
	{
		return static_cast<typename std::remove_reference<T>::type&&>(arg);
	}

    template <typename ForwardIt1, typename ForwardIt2>
    void iter_swap(ForwardIt1 a, ForwardIt2 b)
    {
        typename IteratorTraits<ForwardIt1>::value_type temp = move(*a);
        *a = move(*b);
        *b = move(temp);
    }


    template <typename ForwardIt>
    ForwardIt unique(ForwardIt first, ForwardIt last) 
    {
        if (first == last) 
        {
            return last;
        }

        // result ָ�������е���һ�����ظ�Ԫ��Ӧ�÷��õ�λ��
        ForwardIt result = first;
        ++first;
        for (; first != last; ++first) 
        {
            if (!(*result == *first)) 
            {
                // �����ǰԪ����ǰһ��Ԫ�ز���ȣ����ƶ���
                *(++result) = move(*first);
            }
        }

        // �����µ�"�߼���β"
        return ++result;
    }

    template <typename InputIt, typename T>
    InputIt find(InputIt first, InputIt last, const T& value) 
    {
        while (first != last) 
        {
            if (*first == value)
            {
                return first;
            }
            ++first;
        }
        return last;
    }


    template <typename ForwardIt, typename T>
    ForwardIt remove(ForwardIt first, ForwardIt last, const T& value) 
    {
        // �ҵ���һ����Ҫ�Ƴ���Ԫ��
        first = find(first, last, value);
        if (first == last) 
        {
            return last;
        }

        // result ��һ��������������ָʾ��һ��Ԫ��Ӧ�÷��õ�λ��
        ForwardIt result = first;
        ++first;
        for (; first != last; ++first) 
        {
            if (!(*first == value))
            {
                // �����ǰԪ����ָ����ֵ��ƥ�䣬���ƶ���
                *(result++) = move(*first);
            }
        }

        // �����µ�"�߼���β"
        return result;
    }
    
    template<class T>
    void swap(T& x, T& y)
    {
        T tmp = x;
        x = y;
        y = tmp;
    }

    template <typename BidirectionalIt>
    void reverse(BidirectionalIt first, BidirectionalIt last) 
    {
        while ((first != last) && (first != --last)) 
        {
            std::iter_swap(first++, last);  // ��������Ԫ�ص�ֵ
        }
    }

    template <typename ForwardIt>
    void rotate(ForwardIt first, ForwardIt middle, ForwardIt last) 
    {
        if (first == middle || middle == last) 
        {
            return;
        }
        reverse(first, middle);
        reverse(middle, last);
        reverse(first, last);
    }

    // �������������Ʒ�Χ�ڵ�Ԫ�ص�Ŀ��λ��
    template <typename InputIt, typename OutputIt>
    OutputIt copy(InputIt first, InputIt last, OutputIt d_first) 
    {
        while (first != last) 
        {
            *d_first++ = *first++;
        }
        return d_first;
    }

    template <typename InputIt1, typename InputIt2, typename OutputIt>
    OutputIt merge(InputIt1 first1, InputIt1 last1,
                   InputIt2 first2, InputIt2 last2,
                   OutputIt d_first) 
    {
        while (first1 != last1) 
        {
            if (first2 == last2) 
            {
                return std::copy(first1, last1, d_first);
            }
            if (*first2 < *first1) 
            {
                *d_first++ = *first2++;
            }
            else 
            {
                *d_first++ = *first1++;
            }
        }
        return std::copy(first2, last2, d_first);
    }

}