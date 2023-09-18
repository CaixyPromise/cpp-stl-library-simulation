#ifndef STACK_HPP
#define STACK_HPP
#include <deque>
#include <cassert>
#include "common.hpp"



namespace syu_stack
{


#ifndef __STL_LIMITED_DEFAULT_TEMPLATES
    template <class T, class Sequence = deque<T> >
#else
    template <class T, class Sequence>
#endif
    class stack
    {
    public:
        typedef typename Sequence::value_type value_type;
        typedef typename Sequence::size_type size_type;
        typedef typename Sequence::reference reference;

    protected:
        Sequence _container;

    public:
        stack() = default;

        void push(const T& x)
        {
            _container.push_back(x);
        }

        void pop()
        {
            assert(!_container.empty());
            _container.pop_back();
        }

        T& top()
        {
            assert(!_container.empty());
            return _container.back();
        }

        const T& top() const
        {
            return _container.back();
        }

        size_t size() const
        {
            return _container.size();
        }

        bool empty() const
        {
            return _container.empty();
        }
    };
}


namespace Test_Stack
{
    using namespace syu_stack;

    void test_push_pop_top()
    {
        stack<int> s;

        assert(s.empty());
        output_log("stack", "Initially, the stack should be empty.");

        s.push(1);
        assert(s.top() == 1);

        s.push(2);
        assert(s.top() == 2);

        s.push(3);
        assert(s.top() == 3);
        output_log("stack", "Push elements and test top");

        s.pop();
        assert(s.top() == 2);

        s.pop();
        assert(s.top() == 1);

        s.pop();
        assert(s.empty());
        output_log("stack", "Pop elements and test top");

    }

    void callTestFunction() 
    {
        test_push_pop_top();
        output_log("stack", "All stack tests passed!");     
    }
}


#endif // STACK_HPP
