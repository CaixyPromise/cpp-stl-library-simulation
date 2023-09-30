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

        // result 指向容器中的下一个不重复元素应该放置的位置
        ForwardIt result = first;
        ++first;
        for (; first != last; ++first)
        {
            if (!(*result == *first))
            {
                // 如果当前元素与前一个元素不相等，则移动它
                *(++result) = move(*first);
            }
        }

        // 返回新的"逻辑结尾"
        return ++result;
    }

    // 序列查找指定的元素
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

    // 移除操作
    template <typename ForwardIt, typename T>
    ForwardIt remove(ForwardIt first, ForwardIt last, const T& value)
    {
        // 找到第一个需要移除的元素
        first = find(first, last, value);
        if (first == last)
        {
            return last;
        }

        // result 是一个迭代器，用于指示下一个元素应该放置的位置
        ForwardIt result = first;
        ++first;
        for (; first != last; ++first)
        {
            if (!(*first == value))
            {
                // 如果当前元素与指定的值不匹配，则移动它
                *(result++) = move(*first);
            }
        }

        // 返回新的"逻辑结尾"
        return result;
    }

    template<class T>
    void swap(T& x, T& y)
    {
        T tmp = x;
        x = y;
        y = tmp;
    }

    // 逆置操作
    template <typename BidirectionalIt>
    void reverse(BidirectionalIt first, BidirectionalIt last)
    {
        while ((first != last) && (first != --last))
        {
            std::swap(*(first++), *last);  // 交换两个元素的值
        }
    }

    // 移动旋转操作
    /*
    将 [first, middle) 范围内的元素逆序。
    将 [middle, last) 范围内的元素逆序。
    将整个 [first, last) 范围内的元素逆序。

    这三个逆序操作的组合会让 [middle, last) 范围内的元素移到前面，
    而 [first, middle) 范围内的元素移到后面，从而实现了旋转的效果。
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

    // 复制范围内的元素到目标位置
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

    // sort 实现，使用快排的策略
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