#ifndef ALGORITHM_HPP
#define ALGORITHM_HPP
#pragma once

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

    // ���в���ָ����Ԫ��
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

    // �Ƴ�����
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

    // ���ò���
    template <typename BidirectionalIt>
    void reverse(BidirectionalIt first, BidirectionalIt last)
    {
        while ((first != last) && (first != --last))
        {
            std::swap(*(first++), *last);  // ��������Ԫ�ص�ֵ
        }
    }

    // �ƶ���ת����
    /*
    �� [first, middle) ��Χ�ڵ�Ԫ������
    �� [middle, last) ��Χ�ڵ�Ԫ������
    ������ [first, last) ��Χ�ڵ�Ԫ������

    �����������������ϻ��� [middle, last) ��Χ�ڵ�Ԫ���Ƶ�ǰ�棬
    �� [first, middle) ��Χ�ڵ�Ԫ���Ƶ����棬�Ӷ�ʵ������ת��Ч����
    */
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

    // ���Ʒ�Χ�ڵ�Ԫ�ص�Ŀ��λ��
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
                return copy(first1, last1, d_first);
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
        return copy(first2, last2, d_first);
    }

    template <typename InputIt>
    typename IteratorTraits<InputIt>::difference_type
        _distance(InputIt first, InputIt last, std::input_iterator_tag) 
    {
        typename IteratorTraits<InputIt>::difference_type n = 0;
        while (first != last) 
        {
            ++first;
            ++n;
        }
        return n;
    }

    template <typename RandomIt>
    typename IteratorTraits<RandomIt>::difference_type
        _distance(RandomIt first, RandomIt last, std::random_access_iterator_tag) 
    {
        return last - first;
    }

    template <typename It>
    typename IteratorTraits<It>::difference_type
        distance(It first, It last) 
    {
        return _distance(first, last, typename IteratorTraits<It>::iterator_category());
    }


    template <typename RandomIt>
    RandomIt partition(RandomIt first, RandomIt last) 
    {
        RandomIt pivot = first + distance(first, last) / 2;
        typename IteratorTraits<RandomIt>::value_type pivotValue = *pivot;
        --last;

        while (true) 
        {
            while (*first < pivotValue)
            {
                ++first;
            }
            while (pivotValue < *last)
            {
                --last;
            }

            if (first >= last)
            {
                return first;
            }

            swap(*first, *last);
            ++first;
            --last;
        }
    }

    // sort ʵ�֣�ʹ�ÿ��ŵĲ���
    template <typename RandomIt>
    void sort(RandomIt first, RandomIt last) 
    {
        if (first >= last) 
            return;
        RandomIt pivot = partition(first, last);
        sort(first, pivot);
        sort(pivot, last);
    }
}
#endif // !ALGORITHM_HPP