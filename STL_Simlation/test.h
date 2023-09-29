#ifndef TEST_H
#define TEST_H
#pragma once


#include "vector.hpp"
#include "string.hpp"
#include "list.hpp"
#include "stack.hpp"
#include "queue.hpp"
#include "algorithm.hpp"
//#include "reverse_iterator.hpp" 

void test_string()
{
	Test_string::callTestFunction();

}

void test_vector()
{
	Test_Vector::callTestFunction();
}


void test_list()
{
	Test_list::callTestFunction();
}

void test_stack()
{
	Test_Stack::callTestFunction();
}

void test_queue()
{
	Test_Queue::callTestFunction();
}

#endif // TEST_H